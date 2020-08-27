/*
  ==============================================================================

    DelayGui.h
    Created: 6 Jul 2020 11:29:55pm
    Author:  Ante

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DelayGui  : public juce::Component
{
public:
    DelayGui();
    ~DelayGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::Slider& getTimeSlider() { return timeSlider; }
    juce::Slider& getFeedbackSlider() { return feedbackSlider; }
    juce::Slider& getDelayMixSlider() { return delayMixSlider; }
    juce::ToggleButton& getDelayBypassButton() { return delayBypass; }

private:
    juce::Slider timeSlider;
    juce::Slider feedbackSlider;
    juce::Slider delayMixSlider;
    juce::ToggleButton delayBypass;

    juce::Label timeLabel;
    juce::Label feedbackLabel;
    juce::Label delayMixLabel;
    juce::Label delayBypassLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayGui)
};
