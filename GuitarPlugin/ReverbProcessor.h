/*
  ==============================================================================

    ReverbProcessor.h
    Created: 8 Jul 2020 2:54:13pm
    Author:  Ante

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class ReverbProcessor : public juce::dsp::ProcessorBase
{
public:
    ReverbProcessor(GuitarPluginAudioProcessor&);
    ~ReverbProcessor();

    void prepare(const juce::dsp::ProcessSpec&) override;
    void process(const juce::dsp::ProcessContextReplacing<float>&) override;
    void reset() override;

private:
    GuitarPluginAudioProcessor& audioProcessor;

    juce::dsp::Reverb reverb;
    juce::dsp::Reverb::Parameters reverbParameters;

};