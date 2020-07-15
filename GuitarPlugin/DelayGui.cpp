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

    // DRY GAIN
    dryGainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    dryGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&dryGainSlider);

    dryGainLabel.setText("Dry Gain", juce::NotificationType::dontSendNotification);
    dryGainLabel.setJustificationType(juce::Justification::centred);
    dryGainLabel.attachToComponent(&dryGainSlider, false);

    // WET GAIN
    wetGainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    wetGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&wetGainSlider);

    wetGainLabel.setText("Wet Gain", juce::NotificationType::dontSendNotification);
    wetGainLabel.setJustificationType(juce::Justification::centred);
    wetGainLabel.attachToComponent(&wetGainSlider, false);

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
}

void DelayGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    timeSlider.setBounds((getWidth() / 5) * 1 - 50, (getHeight() / 2) - 40, 100, 100);
    dryGainSlider.setBounds((getWidth() / 5) * 2 - 50, (getHeight() / 2) - 40, 100, 100);
    wetGainSlider.setBounds((getWidth() / 5) * 3 - 50, (getHeight() / 2) - 40, 100, 100);
    delayBypass.setBounds((getWidth() / 5) * 4 - 50, (getHeight() / 2) - 5, 100, 30);
}
