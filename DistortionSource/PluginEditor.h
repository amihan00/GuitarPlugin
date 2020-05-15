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
class DistortionPluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DistortionPluginAudioProcessorEditor (DistortionPluginAudioProcessor&);
    ~DistortionPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistortionPluginAudioProcessor& processor;
    
    Slider volumeSlider;
    Slider gainSlider;
    Slider driveSlider;
    Slider blendSlider;

    Label volumeLabel;
    Label gainLabel;
    Label driveLabel;
    Label blendLabel;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> volumeAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> blendAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPluginAudioProcessorEditor)
};
