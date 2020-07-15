/*
  ==============================================================================

    ReverbGui.h
    Created: 8 Jul 2020 2:53:53pm
    Author:  Ante

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReverbGui  : public juce::Component
{
public:
    ReverbGui();
    ~ReverbGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::Slider& getRoomSizeSlider() { return roomSizeSlider; }
    juce::Slider& getDampingSlider() { return dampingSlider; }
    juce::Slider& getWetLevelSlider() { return wetLevelSlider; }
    juce::Slider& getDryLevelSlider() { return dryLevelSlider; }
    juce::Slider& getWidthSlider() { return widthSlider; }
    juce::Slider& getFreezeModeSlider() { return freezeModeSlider; }
    juce::ToggleButton& getReverbBypassButton() { return reverbBypass; }

private:
    juce::Slider roomSizeSlider;
    juce::Slider dampingSlider;
    juce::Slider wetLevelSlider;
    juce::Slider dryLevelSlider;
    juce::Slider widthSlider;
    juce::Slider freezeModeSlider;
    juce::ToggleButton reverbBypass;

    juce::Label roomSizeLabel;
    juce::Label dampingLabel;
    juce::Label wetLevelLabel;
    juce::Label dryLevelLabel;
    juce::Label widthLabel;
    juce::Label freezeModeLabel;
    juce::Label reverbBypassLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbGui)
};
