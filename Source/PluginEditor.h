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
class GuitarPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                 juce::Button::Listener
{
public:
    GuitarPluginAudioProcessorEditor(GuitarPluginAudioProcessor&);
    ~GuitarPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

    juce::Colour reverbColour = juce::Colour(182, 252, 255);

private:
    DistortionGui distortionGui;
    DelayGui      delayGui;
    ReverbGui     reverbGui;

    juce::DrawableText     pluginName;
    juce::Rectangle<float> backgroundArea;
    juce::Image            background;

    // DISTORTION VARIABLES
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> toneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distortionMixAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> clipButtonsAttachment;
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
    juce::TextButton distortionBypass { "DISTORTION" };
    juce::TextButton delayBypass      { "DELAY" };
    juce::TextButton reverbBypass     { "REVERB" };

    juce::LookAndFeel_V4 pluginLAF;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GuitarPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarPluginAudioProcessorEditor)
};
