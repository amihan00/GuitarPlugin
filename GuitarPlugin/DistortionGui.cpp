/*
  ==============================================================================

    DistortionGui.cpp
    Created: 6 Jul 2020 10:47:52pm
    Author:  Ante

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionGui.h"

//==============================================================================
DistortionGui::DistortionGui()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(600, 150);

    // TONE
    toneSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    toneSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    toneSlider.setLookAndFeel(&distortionLAF);
    addAndMakeVisible(&toneSlider);

    toneLabel.setText("Tone", juce::NotificationType::dontSendNotification);
    toneLabel.setJustificationType(juce::Justification::centredTop);
    toneLabel.attachToComponent(&toneSlider, false);

    // GAIN
    gainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    gainSlider.setLookAndFeel(&distortionLAF);
    addAndMakeVisible(&gainSlider);

    gainLabel.setText("Gain", juce::NotificationType::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centredTop);
    gainLabel.attachToComponent(&gainSlider, false);

    // MIX
    distortionMixSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    distortionMixSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    distortionMixSlider.setLookAndFeel(&distortionLAF);
    addAndMakeVisible(&distortionMixSlider);

    distortionMixLabel.setText("Mix", juce::NotificationType::dontSendNotification);
    distortionMixLabel.setJustificationType(juce::Justification::centredTop);
    distortionMixLabel.attachToComponent(&distortionMixSlider, false);

    // CLIPPING SELECTION
    clipMenu.addItem("atan", atanSoftClip);
    clipMenu.addItem("hard", hardClip);
    clipMenu.addItem("cube", cubeClip);
    addAndMakeVisible(&clipMenu);

    clipMenuLabel.setText("Clipping function", juce::NotificationType::dontSendNotification);
    clipMenuLabel.setJustificationType(juce::Justification::centredTop);
    clipMenuLabel.attachToComponent(&clipMenu, false);

    // DISTORTION BYPASS
    addAndMakeVisible(&distortionBypass);

    distortionBypassLabel.setText("Bypass", juce::NotificationType::dontSendNotification);
    distortionBypassLabel.setJustificationType(juce::Justification::centred);
    distortionBypassLabel.attachToComponent(&distortionBypass, false);

    // LOOK AND FEEL
    distortionLAF.setColour(juce::Slider::thumbColourId, juce::Colours::green);
}

DistortionGui::~DistortionGui()
{
}

void DistortionGui::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::green);
    g.drawRect(getLocalBounds(), 5.0f);
}

void DistortionGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    toneSlider.setBounds(((getWidth() / 3) * 1) - 35, (getHeight() / 4 * 1) - 40, 70, 70);
    gainSlider.setBounds(((getWidth() / 3) * 2) - 35, (getHeight() / 4 * 1) - 40, 70, 70);
    distortionMixSlider.setBounds(((getWidth() / 3) * 1) - 35, (getHeight() / 4 * 2) - 40, 70, 70);
    clipMenu.setBounds(((getWidth() / 3) * 2) - 35, (getHeight() / 4 * 2) - 15, 70, 30);
    distortionBypass.setBounds(((getWidth() / 6) * 5) - 50, (getHeight() / 4 * 3) - 5, 100, 30);
}
