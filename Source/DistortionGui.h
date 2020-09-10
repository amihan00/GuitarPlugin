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
    juce::TextButton& getClipButtons() { return atanClipButton; }

private:
    int clipButtonsId{ 1001 };
    const juce::Colour distortionColour = juce::Colours::green;

    juce::LookAndFeel_V4 distortionLAF;

    juce::Slider     toneSlider;
    juce::Slider     gainSlider;
    juce::Slider     distortionMixSlider;
    juce::TextButton atanClipButton{ "SOFT CLIP" };
    juce::TextButton hardClipButton{ "HARD CLIP" };

    juce::Label toneLabel;
    juce::Label gainLabel;
    juce::Label distortionMixLabel;
    juce::Label clipMenuLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionGui)
};
