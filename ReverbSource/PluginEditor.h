/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ReverbPluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ReverbPluginAudioProcessorEditor (ReverbPluginAudioProcessor&);
    ~ReverbPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ReverbPluginAudioProcessor& processor;

    Slider roomSizeSlider;
    Slider dampingSlider;
    Slider wetLevelSlider;
    Slider dryLevelSlider;
    Slider widthSlider;
    Slider freezeModeSlider;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> roomSizeSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> dampingSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> wetLevelSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> dryLevelSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> widthSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> freezeModeSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbPluginAudioProcessorEditor)
};
