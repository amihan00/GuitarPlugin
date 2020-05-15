/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionPluginAudioProcessorEditor::DistortionPluginAudioProcessorEditor (DistortionPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 150);

    // VOLUME
    volumeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    volumeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&volumeSlider);

    volumeAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTreeState(), "volume", volumeSlider);

    volumeLabel.setFont(15.0f);
    volumeLabel.setText("Volume", NotificationType::dontSendNotification);
    volumeLabel.setJustificationType(Justification::centredTop);
    volumeLabel.attachToComponent(&volumeSlider, false);

    // GAIN
    gainSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&gainSlider);
    
    gainAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTreeState(), "gain", gainSlider);

    gainLabel.setFont(15.0f);
    gainLabel.setText("Gain", NotificationType::dontSendNotification);
    gainLabel.setJustificationType(Justification::centredTop);
    gainLabel.attachToComponent(&gainSlider, false);

    // DRIVE
    driveSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    driveSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    driveSlider.setSkewFactorFromMidPoint(10.0f);
    addAndMakeVisible(&driveSlider);

    driveAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTreeState(), "drive", driveSlider);

    driveLabel.setFont(15.0f);
    driveLabel.setText("Drive", NotificationType::dontSendNotification);
    driveLabel.setJustificationType(Justification::centredTop);
    driveLabel.attachToComponent(&driveSlider, false);

    // BLEND
    blendSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    blendSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&blendSlider);

    blendAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTreeState(), "blend", blendSlider);

    blendLabel.setFont(15.0f);
    blendLabel.setText("Blend", NotificationType::dontSendNotification);
    blendLabel.setJustificationType(Justification::centredTop);
    blendLabel.attachToComponent(&blendSlider, false);
}

DistortionPluginAudioProcessorEditor::~DistortionPluginAudioProcessorEditor()
{
}

//==============================================================================
void DistortionPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void DistortionPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    volumeSlider.setBounds(((getWidth() / 5) * 1) - 50, getHeight() / 2 - 40, 100, 100);
    gainSlider.setBounds(((getWidth() / 5) * 2) - 50, getHeight() / 2 - 40, 100, 100);
    driveSlider.setBounds(((getWidth() / 5) * 3) - 50, getHeight() / 2 - 40, 100, 100);
    blendSlider.setBounds(((getWidth() / 5) * 4) - 50, getHeight() / 2 - 40, 100, 100);
}
