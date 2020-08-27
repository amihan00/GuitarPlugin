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
    juce::Slider& getReverbMixSlider() { return reverbMixSlider; }
    juce::Slider& getWidthSlider() { return widthSlider; }
    juce::ToggleButton& getReverbBypassButton() { return reverbBypass; }

private:
    juce::Slider roomSizeSlider;
    juce::Slider dampingSlider;
    juce::Slider reverbMixSlider;
    juce::Slider widthSlider;
    juce::ToggleButton reverbBypass;

    juce::Label roomSizeLabel;
    juce::Label dampingLabel;
    juce::Label reverbMixLabel;
    juce::Label widthLabel;
    juce::Label reverbBypassLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbGui)
};
