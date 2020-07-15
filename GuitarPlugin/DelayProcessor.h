/*
  ==============================================================================

    DelayProcessor.h
    Created: 7 Jul 2020 1:57:39pm
    Author:  Ante

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class DelayProcessor : public juce::dsp::ProcessorBase
{
public:
    DelayProcessor(GuitarPluginAudioProcessor&);
    ~DelayProcessor();

    void prepare(const juce::dsp::ProcessSpec&) override;
    void process(const juce::dsp::ProcessContextReplacing<float>&) override;
    void reset() override;

private:
    GuitarPluginAudioProcessor& audioProcessor;

    juce::AudioBuffer<float> dryBuffer;
    juce::AudioBuffer<float> delayBuffer;

    juce::dsp::AudioBlock<const float> block;

    int writePosition{ 0 };
    int expectedReadPosition{ 0 };
    double mSampleRate{ 44100 };
    float lastDryGain{ 0.0f };
    float lastWetGain{ 0.0f };

    void getFromDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, const int readPosition, float startGain, float endGain);
    void fillDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, float startGain, float endGain, bool replacing);

};

