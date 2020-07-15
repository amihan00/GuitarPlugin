/*
  ==============================================================================

    ReverbGui.cpp
    Created: 8 Jul 2020 2:53:53pm
    Author:  Ante

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbGui.h"

//==============================================================================
ReverbGui::ReverbGui()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(600, 150);

    // ROOM SIZE
    roomSizeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    roomSizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&roomSizeSlider);

    roomSizeLabel.setText("Room Size", juce::NotificationType::dontSendNotification);
    roomSizeLabel.setJustificationType(juce::Justification::centredTop);
    roomSizeLabel.attachToComponent(&roomSizeSlider, false);

    // DAMPING
    dampingSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dampingSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&dampingSlider);

    dampingLabel.setText("Damping", juce::NotificationType::dontSendNotification);
    dampingLabel.setJustificationType(juce::Justification::centredTop);
    dampingLabel.attachToComponent(&dampingSlider, false);

    // WET LEVEL
    wetLevelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&wetLevelSlider);

    wetLevelLabel.setText("Wet Level", juce::NotificationType::dontSendNotification);
    wetLevelLabel.setJustificationType(juce::Justification::centredTop);
    wetLevelLabel.attachToComponent(&wetLevelSlider, false);

    // DRY LEVEL
    dryLevelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dryLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&dryLevelSlider);

    dryLevelLabel.setText("Dry Level", juce::NotificationType::dontSendNotification);
    dryLevelLabel.setJustificationType(juce::Justification::centredTop);
    dryLevelLabel.attachToComponent(&dryLevelSlider, false);

    // WITDH
    widthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    widthSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&widthSlider);

    widthLabel.setText("Width", juce::NotificationType::dontSendNotification);
    widthLabel.setJustificationType(juce::Justification::centredTop);
    widthLabel.attachToComponent(&widthSlider, false);

    // FREEZE MODE
    freezeModeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freezeModeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&freezeModeSlider);

    freezeModeLabel.setText("Freeze Mode", juce::NotificationType::dontSendNotification);
    freezeModeLabel.setJustificationType(juce::Justification::centredTop);
    freezeModeLabel.attachToComponent(&freezeModeSlider, false);

    // REVERB BYPASS
    addAndMakeVisible(&reverbBypass);

    reverbBypassLabel.setText("Bypass", juce::NotificationType::dontSendNotification);
    reverbBypassLabel.setJustificationType(juce::Justification::centred);
    reverbBypassLabel.attachToComponent(&reverbBypass, false);
}

ReverbGui::~ReverbGui()
{
}

void ReverbGui::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
}

void ReverbGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    roomSizeSlider.setBounds((((getWidth() / 8) * 1) - 50), ((getHeight() / 2) - 40), 100, 100);
    dampingSlider.setBounds((((getWidth() / 8) * 2) - 50), ((getHeight() / 2) - 40), 100, 100);
    wetLevelSlider.setBounds((((getWidth() / 8) * 3) - 50), ((getHeight() / 2) - 40), 100, 100);
    dryLevelSlider.setBounds((((getWidth() / 8) * 4) - 50), ((getHeight() / 2) - 40), 100, 100);
    widthSlider.setBounds((((getWidth() / 8) * 5) - 50), ((getHeight() / 2) - 40), 100, 100);
    freezeModeSlider.setBounds((((getWidth() / 8) * 6) - 50), ((getHeight() / 2) - 40), 100, 100);
    reverbBypass.setBounds((((getWidth() / 8) * 7) - 50), ((getHeight() / 2) - 5), 100, 30);
}
