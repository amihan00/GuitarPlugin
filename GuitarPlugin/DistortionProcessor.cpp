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
    juce::File dir = "C:/guitar_amp.wav";

    waveShaperProcessor.functionToUse = [](float x)
    {
        return (2.0f / juce::float_Pi) * atan(x);
    };

    convolutionProcessor.loadImpulseResponse(dir,
        juce::dsp::Convolution::Stereo::yes,
        juce::dsp::Convolution::Trim::no,
        1024);

    distortionChain.reset();
    dryWetMixer.reset();

    distortionChain.prepare(spec);
    dryWetMixer.prepare(spec);

    distortionChain.setBypassed<highPassFilterIndex> (true);
    distortionChain.setBypassed<gainIndex> (true);
    distortionChain.setBypassed<waveShaperIndex> (true);
    distortionChain.setBypassed<peakFilterIndex> (true);
    distortionChain.setBypassed<convolutionIndex> (true);

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
    auto& highPassFilterProcessor = distortionChain.template get<highPassFilterIndex>();
    auto& gainProcessor = distortionChain.template get<gainIndex>();
    auto& peakFilterProcessor = distortionChain.template get<peakFilterIndex>();

    float cutoff = *audioProcessor.getValueTreeState().getRawParameterValue("tone");
    float gain = *audioProcessor.getValueTreeState().getRawParameterValue("gain");

    *highPassFilterProcessor.state = *juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(audioProcessor.getSampleRate(), cutoff);
    gainProcessor.setGainLinear(gain);
    *peakFilterProcessor.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(audioProcessor.getSampleRate(), 500.0f, 1.5f, 0.1f);
}

void DistortionProcessor::setClippingFunction()
{
    auto& waveShaperProcessor = distortionChain.template get<waveShaperIndex>();
    float clipFunction = *audioProcessor.getValueTreeState().getRawParameterValue("clip");

    switch (int(clipFunction))
    {
    case atanSoftClip:
        waveShaperProcessor.functionToUse = [](float x)
        {
            return (2.0f / juce::float_Pi) * atan(x);
        };
        break;

    case hardClip:
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

    case cubeClip:
        waveShaperProcessor.functionToUse = [](float x)
        {
            return x * x * x;
        };
        break;

    default:
        break;
    }
}
