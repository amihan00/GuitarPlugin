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
    timeSlider.setLookAndFeel(&delayLAF);

    timeLabel.setText("Time", juce::NotificationType::dontSendNotification);
    timeLabel.setJustificationType(juce::Justification::centred);
    timeLabel.setOpaque(false);

    addAndMakeVisible(&timeLabel);
    addAndMakeVisible(&timeSlider);

    // FEEDBACK
    feedbackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    feedbackSlider.setLookAndFeel(&delayLAF);

    feedbackLabel.setText("Feedback", juce::NotificationType::dontSendNotification);
    feedbackLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(&feedbackLabel);
    addAndMakeVisible(&feedbackSlider);

    // MIX
    delayMixSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    delayMixSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    delayMixSlider.setLookAndFeel(&delayLAF);

    delayMixLabel.setText("Mix", juce::NotificationType::dontSendNotification);
    delayMixLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(&delayMixLabel);
    addAndMakeVisible(&delayMixSlider);

    // LOOK AND FEEL
    delayLAF.setColour(juce::Slider::thumbColourId, juce::Colours::transparentWhite);
    delayLAF.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(24, 98, 255));
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

    // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colour(97, 129, 209));
    g.drawRect(getLocalBounds(), 2.0f);
}

void DelayGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    timeSlider.setBounds((getWidth() / 3) * 1 - 45, (getHeight() / 3 * 1) - 45, 90, 90);
    feedbackSlider.setBounds((getWidth() / 3) * 2 - 45, (getHeight() / 3 * 1) - 45, 90, 90);
    delayMixSlider.setBounds((getWidth() / 2) * 1 - 45, (getHeight() / 3 * 2) - 45, 90, 90);

    timeLabel.setBounds(((getWidth() / 3) * 1) - 35, (getHeight() / 3 * 1) - 60, 70, 20);
    feedbackLabel.setBounds(((getWidth() / 3) * 2) - 50, (getHeight() / 3 * 1) - 60, 100, 20);
    delayMixLabel.setBounds(((getWidth() / 3) * 1.5f) - 35, (getHeight() / 3 * 2) - 60, 70, 20);
}
