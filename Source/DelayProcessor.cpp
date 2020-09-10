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
    const int delayBufferSize = 2 * ((int)spec.sampleRate + spec.maximumBlockSize);
    sampleRate = spec.sampleRate;

    expectedReadPosition = -1;

    delayBuffer.setSize(numInputChannels, delayBufferSize);
    delayBuffer.clear();
    
    dryWetMixer.reset();

    dryBuffer.setSize(numInputChannels, spec.maximumBlockSize);
    dryBuffer.clear();

    dryWetMixer.prepare(spec);
}

void DelayProcessor::process(const juce::dsp::ProcessContextReplacing<float>& context)
{
    auto totalNumInputChannels = audioProcessor.getTotalNumInputChannels();
    auto totalNumOutputChannels = audioProcessor.getTotalNumOutputChannels();
    
    const juce::dsp::AudioBlock<float>& block = context.getOutputBlock();

    const float time = *audioProcessor.getValueTreeState().getRawParameterValue("time");
    const float feedback = *audioProcessor.getValueTreeState().getRawParameterValue("feedback");
    const float mix = *audioProcessor.getValueTreeState().getRawParameterValue("delayMix");

    dryBuffer.setSize(audioProcessor.getTotalNumInputChannels(), (int)context.getInputBlock().getNumSamples());
    block.copyTo(dryBuffer);

    dryWetMixer.pushDrySamples(block);
    dryWetMixer.setWetMixProportion(mix);

    int readPosition = static_cast<int>((delayBuffer.getNumSamples() + writePosition - (sampleRate * time / 1000))) % delayBuffer.getNumSamples();

    // Copy the initial signal to the delay buffer at -writePosition
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        fillDelayBuffer(dryBuffer, channel, 1.0f, 1.0f, true);
    }
    
    // Remove the initial signal
    dryBuffer.applyGainRamp(0, dryBuffer.getNumSamples(), 0.0f, 0.0f);

    // Get the delayed signal from readPosition and copy it further to the delay buffer
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

        fillDelayBuffer(dryBuffer, channel, lastFeedback, feedback, false);
        lastFeedback = feedback;
    }

    // Mix the initial signal with the delayed signals
    block.copyFrom(dryBuffer);
    dryWetMixer.mixWetSamples(block);

    // Amplify the complete signal in relation to the mix value
    gainFactor = (float)(-(abs(mix * 2 - 1.0f) - 2.0f));
    gain.setGainLinear(gainFactor);
    gain.process(context);

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
