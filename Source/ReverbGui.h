/*
  ==============================================================================

    ReverbGui.h
    Created: 8 Jul 2020 2:53:53pm
    Author:  Ante

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define REVERB_COLOUR 0x23f4a5

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

private:
    const juce::Colour reverbColour = juce::Colours::red;

    juce::LookAndFeel_V4 reverbLAF;

    juce::Slider roomSizeSlider;
    juce::Slider dampingSlider;
    juce::Slider reverbMixSlider;
    juce::Slider widthSlider;

    juce::Label roomSizeLabel;
    juce::Label dampingLabel;
    juce::Label reverbMixLabel;
    juce::Label widthLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbGui)
};
