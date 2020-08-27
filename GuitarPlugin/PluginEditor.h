/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DistortionGui.h"
#include "DelayGui.h"
#include "ReverbGui.h"

//==============================================================================
/**
*/
class GuitarPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GuitarPluginAudioProcessorEditor (GuitarPluginAudioProcessor&);
    ~GuitarPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DistortionGui distortionGui;
    DelayGui delayGui;
    ReverbGui reverbGui;

    // DISTORTION VARIABLES
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> toneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distortionMixAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> clipMenuAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> distortionBypassAttachment;

    // DELAY VARIABLES
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> timeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayMixAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> delayBypassAttachment;

    // REVERB VARIABLES
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampingSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbMixSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freezeModeSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> reverbBypassAttachment;

    // BYPASS BUTTONS
    juce::ToggleButton distortionBypass;
    juce::ToggleButton delayBypass;
    juce::ToggleButton reverbBypass;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GuitarPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarPluginAudioProcessorEditor)
};
