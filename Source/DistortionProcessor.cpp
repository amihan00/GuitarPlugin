/*
  ==============================================================================

    DistortionProcessor.cpp
    Created: 7 Jul 2020 12:16:09pm
    Author:  Ante

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionProcessor.h"

DistortionProcessor::DistortionProcessor(GuitarPluginAudioProcessor& p) : audioProcessor (p) {}

DistortionProcessor::~DistortionProcessor() {}

void DistortionProcessor::prepare(const juce::dsp::ProcessSpec& spec)
{
    auto& waveShaperProcessor = distortionChain.template get<waveShaperIndex>();
    auto& convolutionProcessor = distortionChain.template get<convolutionIndex>();

    waveShaperProcessor.functionToUse = [](float x)
    {
        return (2.0f / juce::float_Pi) * atan(x);
    };

    convolutionProcessor.loadImpulseResponse(BinaryData::guitar_amp_wav, BinaryData::guitar_amp_wavSize,
        juce::dsp::Convolution::Stereo::yes,
        juce::dsp::Convolution::Trim::no,
        1024);

    distortionChain.reset();
    dryWetMixer.reset();

    distortionChain.prepare(spec);
    dryWetMixer.prepare(spec);
}

void DistortionProcessor::process(const juce::dsp::ProcessContextReplacing<float>& context)
{
    float mix = *audioProcessor.getValueTreeState().getRawParameterValue("distortionMix");

    juce::dsp::AudioBlock<float>& block = context.getOutputBlock();

    dryWetMixer.pushDrySamples(block);
    dryWetMixer.setWetMixProportion(mix);

    updateDistortionParameters();
    setClippingFunction();
    distortionChain.process(context);

    dryWetMixer.mixWetSamples(block);
}

void DistortionProcessor::reset()
{
    distortionChain.reset();
    dryWetMixer.reset();
}

void DistortionProcessor::updateDistortionParameters()
{
    auto& highPassFilterProcessor1 = distortionChain.template get<highPassFilterIndex1>();
    auto& highPassFilterProcessor2 = distortionChain.template get<highPassFilterIndex2>();
    auto& gainProcessor = distortionChain.template get<gainIndex>();
    auto& peakFilterProcessor = distortionChain.template get<peakFilterIndex>();

    float cutoff = *audioProcessor.getValueTreeState().getRawParameterValue("tone");
    float gain = *audioProcessor.getValueTreeState().getRawParameterValue("gain");

    *highPassFilterProcessor1.state = *juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(audioProcessor.getSampleRate(), cutoff);
    *highPassFilterProcessor2.state = *juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(audioProcessor.getSampleRate(), cutoff);

    gainProcessor.setGainLinear(gain);
    *peakFilterProcessor.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(audioProcessor.getSampleRate(), 600.0f, 0.7f, 0.3f);
}

void DistortionProcessor::setClippingFunction()
{
    auto& waveShaperProcessor = distortionChain.template get<waveShaperIndex>();
    bool clipFunction = *audioProcessor.getValueTreeState().getRawParameterValue("clip");

    switch (clipFunction)
    {
    case true:
        waveShaperProcessor.functionToUse = [](float x)
        {
            return (2.0f / juce::float_Pi) * atan(x);
        };
        break;

    case false:
        waveShaperProcessor.functionToUse = [](float x)
        {
            if (x > 1.0f)
                return 1.0f;
            else if (x < -1.0f)
                return -1.0f;
            else
                return x;
        };
        break;

    default:
        break;
    }
}
