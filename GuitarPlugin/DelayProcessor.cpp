/*
  ==============================================================================

    DelayProcessor.cpp
    Created: 7 Jul 2020 1:57:39pm
    Author:  Ante

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayProcessor.h"

DelayProcessor::DelayProcessor(GuitarPluginAudioProcessor& p) : audioProcessor(p)
{
}

DelayProcessor::~DelayProcessor()
{
}

void DelayProcessor::prepare(const juce::dsp::ProcessSpec& spec)
{
    const int numInputChannels = audioProcessor.getTotalNumInputChannels();
    const int delayBufferSize = 2 * (spec.sampleRate + spec.maximumBlockSize);
    sampleRate = spec.sampleRate;

    expectedReadPosition = -1;

    delayBuffer.setSize(numInputChannels, delayBufferSize);
    delayBuffer.clear();

    dryBuffer.setSize(numInputChannels, spec.maximumBlockSize);
    dryBuffer.clear();
}

void DelayProcessor::process(const juce::dsp::ProcessContextReplacing<float>& context)
{
    auto totalNumInputChannels = audioProcessor.getTotalNumInputChannels();
    auto totalNumOutputChannels = audioProcessor.getTotalNumOutputChannels();
    
    dryBuffer.setSize(audioProcessor.getTotalNumInputChannels(), context.getInputBlock().getNumSamples());
    context.getInputBlock().copyTo(dryBuffer);

    const float time = *audioProcessor.getValueTreeState().getRawParameterValue("time");
    const float wetGain = *audioProcessor.getValueTreeState().getRawParameterValue("delayMix");
    const float dryGain = 1.0f - wetGain;

    int readPosition = static_cast<int>((delayBuffer.getNumSamples() + writePosition - (sampleRate * time / 1000))) % delayBuffer.getNumSamples();

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        fillDelayBuffer(dryBuffer, channel, lastWetGain, wetGain, true);
    }

    /*******************************************************************************************************/
    
    dryBuffer.applyGainRamp(0, dryBuffer.getNumSamples(), lastDryGain, dryGain);
    lastDryGain = dryGain;

    /*******************************************************************************************************/

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        if (expectedReadPosition >= 0)
        {
            auto endGain = (readPosition == expectedReadPosition) ? 1.0f : 0.0f;
            getFromDelayBuffer(dryBuffer, channel, expectedReadPosition, 1.0f, endGain);
        }

        if (readPosition != expectedReadPosition)
        {
            getFromDelayBuffer(dryBuffer, channel, readPosition, 0.0f, 1.0f);
        }

        fillDelayBuffer(dryBuffer, channel, lastWetGain, wetGain, false);
        lastWetGain = wetGain;
    }

    context.getOutputBlock().copyFrom(dryBuffer);

    writePosition += dryBuffer.getNumSamples();
    writePosition %= delayBuffer.getNumSamples();

    expectedReadPosition = readPosition + dryBuffer.getNumSamples();
    expectedReadPosition %= delayBuffer.getNumSamples();

    dryBuffer.clear();
}

void DelayProcessor::reset()
{
}

void DelayProcessor::getFromDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, const int readPosition, float startGain, float endGain)
{
    if (delayBuffer.getNumSamples() >= buffer.getNumSamples() + readPosition)
    {
        buffer.addFromWithRamp(channel, 0, delayBuffer.getReadPointer(channel, readPosition), buffer.getNumSamples(), startGain, endGain);
    }
    else if (delayBuffer.getNumSamples() < buffer.getNumSamples() + readPosition)
    {
        const int delayBufferRemaining = delayBuffer.getNumSamples() - readPosition;
        const float midGain = juce::jmap(float(delayBufferRemaining) / buffer.getNumSamples(), startGain, endGain);

        buffer.addFromWithRamp(channel, 0, delayBuffer.getReadPointer(channel, readPosition), delayBufferRemaining, startGain, midGain);
        buffer.addFromWithRamp(channel, delayBufferRemaining, delayBuffer.getReadPointer(channel), buffer.getNumSamples() - delayBufferRemaining, midGain, endGain);
    }
}

void DelayProcessor::fillDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, float startGain, float endGain, bool replacing)
{
    if (delayBuffer.getNumSamples() >= writePosition + buffer.getNumSamples())
    {
        if (replacing)
        {
            delayBuffer.copyFromWithRamp(channel, writePosition, buffer.getReadPointer(channel), buffer.getNumSamples(), startGain, endGain);
        }
        else
        {
            delayBuffer.addFromWithRamp(channel, writePosition, buffer.getReadPointer(channel), buffer.getNumSamples(), startGain, endGain);
        }
    }
    else if (delayBuffer.getNumSamples() < writePosition + buffer.getNumSamples())
    {
        const int delayBufferRemaining = delayBuffer.getNumSamples() - writePosition;
        const float midGain = juce::jmap(float(delayBufferRemaining) / buffer.getNumSamples(), startGain, endGain);

        if (replacing)
        {
            delayBuffer.copyFromWithRamp(channel, writePosition, buffer.getReadPointer(channel), delayBufferRemaining, startGain, midGain);
            delayBuffer.copyFromWithRamp(channel, 0, buffer.getReadPointer(channel, delayBufferRemaining), buffer.getNumSamples(), midGain, endGain);
        }
        else
        {
            delayBuffer.addFromWithRamp(channel, writePosition, buffer.getReadPointer(channel), delayBufferRemaining, startGain, midGain);
            delayBuffer.addFromWithRamp(channel, 0, buffer.getReadPointer(channel, delayBufferRemaining), buffer.getNumSamples(), midGain, endGain);
        }
    }
}

