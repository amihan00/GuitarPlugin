/*
  ==============================================================================

    DistortionProcessor.h
    Created: 7 Jul 2020 12:16:09pm
    Author:  Ante

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class DistortionProcessor : public juce::dsp::ProcessorBase
{
public:
    DistortionProcessor(GuitarPluginAudioProcessor&);
    ~DistortionProcessor();

    void prepare(const juce::dsp::ProcessSpec&) override;
    void process(const juce::dsp::ProcessContextReplacing<float>&) override;
    void reset() override;

private:
    GuitarPluginAudioProcessor& audioProcessor;

    enum
    {
        atanSoftClip,
        hardClip,
        cubeClip
    };

    enum
    {
        highPassFilterIndex,
        gainIndex,
        waveShaperIndex,
        peakFilterIndex,
        convolutionIndex
    };

    juce::dsp::ProcessorChain<juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>>,
        juce::dsp::Gain<float>,
        juce::dsp::WaveShaper<float>,
        juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>>,
        juce::dsp::Convolution> distortionChain;

    juce::dsp::DryWetMixer<float> dryWetMixer;

    void updateDistortionParameters();
    void setClippingFunction();
};
