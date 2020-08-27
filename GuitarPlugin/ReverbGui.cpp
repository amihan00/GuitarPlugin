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

    // MIX
    reverbMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    reverbMixSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&reverbMixSlider);

    reverbMixLabel.setText("Mix", juce::NotificationType::dontSendNotification);
    reverbMixLabel.setJustificationType(juce::Justification::centredTop);
    reverbMixLabel.attachToComponent(&reverbMixSlider, false);

    // WITDH
    widthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    widthSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&widthSlider);

    widthLabel.setText("Width", juce::NotificationType::dontSendNotification);
    widthLabel.setJustificationType(juce::Justification::centredTop);
    widthLabel.attachToComponent(&widthSlider, false);

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

    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds(), 5.0f);
}

void ReverbGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    roomSizeSlider.setBounds((((getWidth() / 3) * 1) - 35), ((getHeight() / 4 * 1) - 40), 70, 70);
    dampingSlider.setBounds((((getWidth() / 3) * 2) - 35), ((getHeight() / 4 * 1) - 40), 70, 70);
    reverbMixSlider.setBounds((((getWidth() / 3) * 1) - 35), ((getHeight() / 4 * 2) - 40), 70, 70);
    widthSlider.setBounds((((getWidth() / 3) * 2) - 35), ((getHeight() / 4 * 2) - 40), 70, 70);
    reverbBypass.setBounds((((getWidth() / 3) * 1) - 50), ((getHeight() / 4 * 3) - 5), 70, 30);
}
