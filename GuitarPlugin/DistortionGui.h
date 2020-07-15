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
    juce::Slider& getBlendSlider() { return blendSlider; }
    juce::ComboBox& getClipMenu() { return clipMenu; }
    juce::ToggleButton& getDistortionBypassButton() { return distortionBypass; }

private:
    enum
    {
        atanSoftClip = 1,
        hardClip
    };

    juce::Slider toneSlider;
    juce::Slider gainSlider;
    juce::Slider blendSlider;
    juce::ComboBox clipMenu;
    juce::ToggleButton distortionBypass;

    juce::Label toneLabel;
    juce::Label gainLabel;
    juce::Label blendLabel;
    juce::Label clipMenuLabel;
    juce::Label distortionBypassLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionGui)
};
