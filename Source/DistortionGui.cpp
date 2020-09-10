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

    toneLabel.setText("Tone", juce::NotificationType::dontSendNotification);
    toneLabel.setJustificationType(juce::Justification::centredTop);

    addAndMakeVisible(&toneLabel);
    addAndMakeVisible(&toneSlider);

    // GAIN
    gainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    gainSlider.setLookAndFeel(&distortionLAF);

    gainLabel.setText("Gain", juce::NotificationType::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centredTop);

    addAndMakeVisible(&gainLabel);
    addAndMakeVisible(&gainSlider);

    // MIX
    distortionMixSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    distortionMixSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    distortionMixSlider.setLookAndFeel(&distortionLAF);

    distortionMixLabel.setText("Mix", juce::NotificationType::dontSendNotification);
    distortionMixLabel.setJustificationType(juce::Justification::centredTop);

    addAndMakeVisible(&distortionMixLabel);
    addAndMakeVisible(&distortionMixSlider);

    // CLIP SELECTION BUTTONS
    atanClipButton.setRadioGroupId(clipButtonsId);
    hardClipButton.setRadioGroupId(clipButtonsId);

    atanClipButton.setClickingTogglesState(true);
    hardClipButton.setClickingTogglesState(true);

    atanClipButton.setConnectedEdges(3);
    atanClipButton.setLookAndFeel(&distortionLAF);
    addAndMakeVisible(&atanClipButton);

    hardClipButton.setConnectedEdges(3);
    hardClipButton.setLookAndFeel(&distortionLAF);
    addAndMakeVisible(&hardClipButton);

    // LOOK AND FEEL
    distortionLAF.setColour(juce::Slider::thumbColourId, juce::Colours::transparentWhite);
    distortionLAF.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(126, 37, 255));

    distortionLAF.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour(126, 37, 255));
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

    g.setColour(juce::Colour(158, 118, 229));
    g.drawRect(getLocalBounds(), 2.0f);
}

void DistortionGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    toneSlider.setBounds(((getWidth() / 3) * 1) - 45, (getHeight() / 3 * 1) - 45, 90, 90);
    gainSlider.setBounds(((getWidth() / 3) * 2) - 45, (getHeight() / 3 * 1) - 45, 90, 90);
    distortionMixSlider.setBounds(((getWidth() / 2) * 1) - 45, (getHeight() / 3 * 2) - 45, 90, 90);

    toneLabel.setBounds(((getWidth() / 3) * 1) - 35, (getHeight() / 3 * 1) - 60, 70, 20);
    gainLabel.setBounds(((getWidth() / 3) * 2) - 35, (getHeight() / 3 * 1) - 60, 70, 20);
    distortionMixLabel.setBounds(((getWidth() / 2) * 1) - 35, (getHeight() / 3 * 2) - 60, 70, 20);

    atanClipButton.setBounds(0, getHeight() - 22, getWidth() / 2, 25);
    hardClipButton.setBounds(getWidth() / 2, getHeight() - 22, getWidth() / 2, 25);
}
