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
    roomSizeSlider.setLookAndFeel(&reverbLAF);

    roomSizeLabel.setText("Room Size", juce::NotificationType::dontSendNotification);
    roomSizeLabel.setJustificationType(juce::Justification::centredTop);

    addAndMakeVisible(&roomSizeLabel);
    addAndMakeVisible(&roomSizeSlider);

    // DAMPING
    dampingSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dampingSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    dampingSlider.setLookAndFeel(&reverbLAF);

    dampingLabel.setText("Damping", juce::NotificationType::dontSendNotification);
    dampingLabel.setJustificationType(juce::Justification::centredTop);

    addAndMakeVisible(&dampingLabel);
    addAndMakeVisible(&dampingSlider);

    // MIX
    reverbMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    reverbMixSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    reverbMixSlider.setLookAndFeel(&reverbLAF);

    reverbMixLabel.setText("Mix", juce::NotificationType::dontSendNotification);
    reverbMixLabel.setJustificationType(juce::Justification::centredTop);

    addAndMakeVisible(&reverbMixLabel);
    addAndMakeVisible(&reverbMixSlider);

    // WITDH
    widthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    widthSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    widthSlider.setLookAndFeel(&reverbLAF);

    widthLabel.setText("Width", juce::NotificationType::dontSendNotification);
    widthLabel.setJustificationType(juce::Justification::centredTop);

    addAndMakeVisible(&widthLabel);
    addAndMakeVisible(&widthSlider);

    // LOOK AND FEEL
    reverbLAF.setColour(juce::Slider::thumbColourId, juce::Colours::transparentWhite);
    reverbLAF.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0, 174, 255));
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

    // g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colour(182, 252, 255));
    g.drawRect(getLocalBounds(), 2.0f);
}

void ReverbGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    roomSizeSlider.setBounds((((getWidth() / 3) * 1) - 45), ((getHeight() / 3 * 1) - 45), 90, 90);
    dampingSlider.setBounds((((getWidth() / 3) * 2) - 45), ((getHeight() / 3 * 1) - 45), 90, 90);
    reverbMixSlider.setBounds((((getWidth() / 3) * 1) - 45), ((getHeight() / 3 * 2) - 45), 90, 90);
    widthSlider.setBounds((((getWidth() / 3) * 2) - 45), ((getHeight() / 3 * 2) - 45), 90, 90);

    roomSizeLabel.setBounds(((getWidth() / 3) * 1) - 50, (getHeight() / 3 * 1) - 60, 100, 20);
    dampingLabel.setBounds(((getWidth() / 3) * 2) - 35, (getHeight() / 3 * 1) - 60, 70, 20);
    reverbMixLabel.setBounds(((getWidth() / 3) * 1) - 35, (getHeight() / 3 * 2) - 60, 70, 20);
    widthLabel.setBounds(((getWidth() / 3) * 2) - 35, (getHeight() / 3 * 2) - 60, 70, 20);
}
