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
}

void ReverbProcessor::process(const juce::dsp::ProcessContextReplacing<float>& context)
{
    reverbParameters.roomSize = *audioProcessor.getValueTreeState().getRawParameterValue("roomSize");
    reverbParameters.damping = *audioProcessor.getValueTreeState().getRawParameterValue("damping");
    reverbParameters.wetLevel = *audioProcessor.getValueTreeState().getRawParameterValue("wetLevel");
    reverbParameters.dryLevel = *audioProcessor.getValueTreeState().getRawParameterValue("dryLevel");
    reverbParameters.width = *audioProcessor.getValueTreeState().getRawParameterValue("width");
    reverbParameters.freezeMode = *audioProcessor.getValueTreeState().getRawParameterValue("freezeMode");
    reverb.setParameters(reverbParameters);

    reverb.process(context);
}

void ReverbProcessor::reset()
{
    reverb.reset();
}