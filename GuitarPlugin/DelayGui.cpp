/*
  ==============================================================================

    DelayGui.cpp
    Created: 6 Jul 2020 11:29:55pm
    Author:  Ante

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayGui.h"

//==============================================================================
DelayGui::DelayGui()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(600, 150);

    // TIME
    timeSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    timeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&timeSlider);

    timeLabel.setText("Time", juce::NotificationType::dontSendNotification);
    timeLabel.setJustificationType(juce::Justification::centred);
    timeLabel.attachToComponent(&timeSlider, false);

    // FEEDBACK
    feedbackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&feedbackSlider);

    feedbackLabel.setText("Feedback", juce::NotificationType::dontSendNotification);
    feedbackLabel.setJustificationType(juce::Justification::centred);
    feedbackLabel.attachToComponent(&feedbackSlider, false);

    // MIX
    delayMixSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    delayMixSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&delayMixSlider);

    delayMixLabel.setText("Mix", juce::NotificationType::dontSendNotification);
    delayMixLabel.setJustificationType(juce::Justification::centred);
    delayMixLabel.attachToComponent(&delayMixSlider, false);

    // DELAY BYPASS
    addAndMakeVisible(&delayBypass);

    delayBypassLabel.setText("Bypass", juce::NotificationType::dontSendNotification);
    delayBypassLabel.setJustificationType(juce::Justification::centred);
    delayBypassLabel.attachToComponent(&delayBypass, false);
}

DelayGui::~DelayGui()
{
}

void DelayGui::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::purple);
    g.drawRect(getLocalBounds(), 5.0f);
}

void DelayGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    timeSlider.setBounds((getWidth() / 3) * 1 - 35, (getHeight() / 4 * 1) - 40, 70, 70);
    feedbackSlider.setBounds((getWidth() / 3) * 2 - 35, (getHeight() / 4 * 1) - 40, 70, 70);
    delayMixSlider.setBounds((getWidth() / 3) * 1.5f - 35, (getHeight() / 4 * 2) - 40, 70, 70);
    delayBypass.setBounds((getWidth() / 4) * 3 - 50, (getHeight() / 4 * 3) - 5, 70, 30);
}
