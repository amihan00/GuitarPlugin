/*
  ==============================================================================

    DistortionGui.h
    Created: 6 Jul 2020 10:47:52pm
    Author:  Ante

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DistortionGui  : public juce::Component
{
public:
    DistortionGui();
    ~DistortionGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::Slider& getToneSlider() { return toneSlider; }
    juce::Slider& getGainSlider() { return gainSlider; }
    juce::Slider& getDistortionMixSlider() { return distortionMixSlider; }
    juce::ComboBox& getClipMenu() { return clipMenu; }
    juce::ToggleButton& getDistortionBypassButton() { return distortionBypass; }

private:
    enum
    {
        atanSoftClip = 1,
        hardClip,
        cubeClip
    };

    juce::Slider toneSlider;
    juce::Slider gainSlider;
    juce::Slider distortionMixSlider;
    juce::ComboBox clipMenu;
    juce::ToggleButton distortionBypass;

    juce::Label toneLabel;
    juce::Label gainLabel;
    juce::Label distortionMixLabel;
    juce::Label clipMenuLabel;
    juce::Label distortionBypassLabel;

    juce::LookAndFeel_V4 distortionLAF;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionGui)
};
