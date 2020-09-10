/*
  ==============================================================================

    ReverbProcessor.cpp
    Created: 8 Jul 2020 2:54:13pm
    Author:  Ante

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbProcessor.h"

ReverbProcessor::ReverbProcessor(GuitarPluginAudioProcessor& p) : audioProcessor(p) {}

ReverbProcessor::~ReverbProcessor() {}

void ReverbProcessor::prepare(const juce::dsp::ProcessSpec& spec)
{
    reverb.reset();
    reverb.prepare(spec);

    reverbParameters.freezeMode = 0.0f;
}

void ReverbProcessor::process(const juce::dsp::ProcessContextReplacing<float>& context)
{
    reverbParameters.roomSize = *audioProcessor.getValueTreeState().getRawParameterValue("roomSize");
    reverbParameters.damping = *audioProcessor.getValueTreeState().getRawParameterValue("damping");
    reverbParameters.wetLevel = *audioProcessor.getValueTreeState().getRawParameterValue("reverbMix");
    reverbParameters.dryLevel = 1.0f - reverbParameters.wetLevel;
    reverbParameters.width = *audioProcessor.getValueTreeState().getRawParameterValue("width");
    reverb.setParameters(reverbParameters);

    reverb.process(context);
}

void ReverbProcessor::reset()
{
    reverb.reset();
}