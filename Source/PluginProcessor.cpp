/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DistortionProcessor.h"
#include "DelayProcessor.h"
#include "ReverbProcessor.h"

//==============================================================================
GuitarPluginAudioProcessor::GuitarPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), state(*this, nullptr, "PARAMETERS", createParameters())
#endif
{
    distortionProcessor = std::make_unique<DistortionProcessor>(*this);
    delayProcessor = std::make_unique<DelayProcessor>(*this);
    reverbProcessor = std::make_unique<ReverbProcessor>(*this);
}

GuitarPluginAudioProcessor::~GuitarPluginAudioProcessor()
{
}

//==============================================================================
const juce::String GuitarPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GuitarPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GuitarPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GuitarPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GuitarPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GuitarPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GuitarPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GuitarPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GuitarPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void GuitarPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GuitarPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    distortionProcessor->reset();
    delayProcessor->reset();
    reverbProcessor->reset();

    distortionProcessor->prepare(spec);
    delayProcessor->prepare(spec);
    reverbProcessor->prepare(spec);
}

void GuitarPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.

    distortionProcessor->reset();
    delayProcessor->reset();
    reverbProcessor->reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GuitarPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void GuitarPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    bool distortionBypass = *state.getRawParameterValue("distortionBypass");
    bool delayBypass = *state.getRawParameterValue("delayBypass");
    bool reverbBypass = *state.getRawParameterValue("reverbBypass");

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

    if (distortionBypass == true)
    {
        distortionProcessor->process(context);
    }

    if (delayBypass == true)
    {
        delayProcessor->process(context);
    }
    
    if (reverbBypass == true)
    {
        reverbProcessor->process(context);
    }
}

//==============================================================================
bool GuitarPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GuitarPluginAudioProcessor::createEditor()
{
    return new GuitarPluginAudioProcessorEditor (*this);
}

//==============================================================================
void GuitarPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GuitarPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout GuitarPluginAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    // DISTORTION PARAMETERS
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("tone", "Tone", 0.1f, 2000.0f, 500.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("gain", "Gain", juce::NormalisableRange<float>(1.0f, 3000.0f, 0.1f, 0.3f), 300.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("distortionMix", "Distortion Mix", 0.0f, 1.0f, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterBool>("clip", "Clip", true));
    parameters.push_back(std::make_unique<juce::AudioParameterBool>("distortionBypass", "Distortion Bypass", true));

    // DELAY PARAMETERS
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("time", "Time", juce::NormalisableRange<float>(0.0f, 2000.0f, 1.0f), 500.0f, "ms"));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("feedback", "Feedback", 0.0f, 1.0f, 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("delayMix", "Delay Mix", 0.0f, 1.0f, 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterBool>("delayBypass", "Delay Bypass", true));

    // REVERB PARAMETERS
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("roomSize", "Room Size", 0.0f, 1.0f, 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("damping", "Damping", 0.0f, 1.0f, 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("reverbMix", "Reverb Mix", 0.0f, 1.0f, 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("width", "Width", 0.0f, 1.0f, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterBool>("reverbBypass", "Reverb Bypass", true));

    return { parameters.begin(), parameters.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GuitarPluginAudioProcessor();
}
