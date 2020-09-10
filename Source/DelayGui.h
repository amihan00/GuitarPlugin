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

private:
    const juce::Colour delayColour = juce::Colours::purple;

    juce::LookAndFeel_V4 delayLAF;

    juce::Slider timeSlider;
    juce::Slider feedbackSlider;
    juce::Slider delayMixSlider;

    juce::Label timeLabel;
    juce::Label feedbackLabel;
    juce::Label delayMixLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayGui)
};
