/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbPluginAudioProcessor::ReverbPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
    state(*this, nullptr, "parameters",
        {
            std::make_unique<AudioParameterFloat>("roomSize", "RoomSize", 0.0f, 1.0f, 0.5f),
            std::make_unique<AudioParameterFloat>("damping", "Damping", 0.0f, 1.0f, 0.5f),
            std::make_unique<AudioParameterFloat>("wetLevel", "WetLevel", 0.0f, 1.0f, 0.33f),
            std::make_unique<AudioParameterFloat>("dryLevel", "DryLevel", 0.0f, 1.0f, 0.4f),
            std::make_unique<AudioParameterFloat>("width", "Width", 0.0f, 1.0f, 1.0f),
            std::make_unique<AudioParameterFloat>("freezeMode", "FreezeMode", 0.0f, 1.0f, 0.0f)
        })
#endif
{
}

ReverbPluginAudioProcessor::~ReverbPluginAudioProcessor()
{
}

//==============================================================================
const String ReverbPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ReverbPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ReverbPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ReverbPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ReverbPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ReverbPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ReverbPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ReverbPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String ReverbPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void ReverbPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ReverbPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    reverb.reset();
    reverb.setSampleRate(sampleRate);
}

void ReverbPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ReverbPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ReverbPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    reverbParameters.roomSize = *state.getRawParameterValue("roomSize");
    reverbParameters.damping = *state.getRawParameterValue("damping");
    reverbParameters.wetLevel = *state.getRawParameterValue("wetLevel");
    reverbParameters.dryLevel = *state.getRawParameterValue("dryLevel");
    reverbParameters.width = *state.getRawParameterValue("width");
    reverbParameters.freezeMode = *state.getRawParameterValue("freezeMode");
    reverb.setParameters(reverbParameters);

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }

    reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
}

//==============================================================================
bool ReverbPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ReverbPluginAudioProcessor::createEditor()
{
    return new ReverbPluginAudioProcessorEditor (*this);
}

//==============================================================================
void ReverbPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ReverbPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReverbPluginAudioProcessor();
}
