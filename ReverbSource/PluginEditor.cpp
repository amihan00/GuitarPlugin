/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbPluginAudioProcessorEditor::ReverbPluginAudioProcessorEditor (ReverbPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    roomSizeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    roomSizeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&roomSizeSlider);

    roomSizeSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTreeState(), "roomSize", roomSizeSlider);

    dampingSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dampingSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&dampingSlider);

    dampingSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTreeState(), "damping", dampingSlider);

    wetLevelSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetLevelSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&wetLevelSlider);

    wetLevelSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTreeState(), "wetLevel", wetLevelSlider);

    dryLevelSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dryLevelSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&dryLevelSlider);

    dryLevelSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTreeState(), "dryLevel", dryLevelSlider);

    widthSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    widthSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&widthSlider);

    widthSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTreeState(), "width", widthSlider);

    freezeModeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freezeModeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&freezeModeSlider);

    freezeModeSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTreeState(), "freezeMode", freezeModeSlider);

}

ReverbPluginAudioProcessorEditor::~ReverbPluginAudioProcessorEditor()
{
}

//==============================================================================
void ReverbPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour(Colours::white);
    g.drawText("Room size", (((getWidth() / 6) * 1) - (100 / 2)), (((getHeight() / 4 + 60) * 1) - (100 / 2)), 100, 100, Justification::centred, false);
    g.drawText("Damping", (((getWidth() / 6) * 3) - (100 / 2)), (((getHeight() / 4 + 60) * 1) - (100 / 2)), 100, 100, Justification::centred, false);
    g.drawText("Wet level", (((getWidth() / 6) * 5) - (100 / 2)), (((getHeight() / 4 + 60) * 1) - (100 / 2)), 100, 100, Justification::centred, false);
    g.drawText("Dry level", (((getWidth() / 6) * 1) - (100 / 2)), (((getHeight() / 4 + 20) * 3) - (100 / 2)), 100, 100, Justification::centred, false);
    g.drawText("Width", (((getWidth() / 6) * 3) - (100 / 2)), (((getHeight() / 4 + 20) * 3) - (100 / 2)), 100, 100, Justification::centred, false);
    g.drawText("FreezeMode", (((getWidth() / 6) * 5) - (100 / 2)), (((getHeight() / 4 + 20) * 3) - (100 / 2)), 100, 100, Justification::centred, false);
}

void ReverbPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    roomSizeSlider.setBounds((((getWidth() / 6) * 1) - (100 / 2)), (((getHeight() / 4) * 1) - (100 / 2)), 100, 100);
    dampingSlider.setBounds((((getWidth() / 6) * 3) - (100 / 2)), (((getHeight() / 4) * 1) - (100 / 2)), 100, 100);
    wetLevelSlider.setBounds((((getWidth() / 6) * 5) - (100 / 2)), (((getHeight() / 4) * 1) - (100 / 2)), 100, 100);
    dryLevelSlider.setBounds((((getWidth() / 6) * 1) - (100 / 2)), (((getHeight() / 4) * 3) - (100 / 2)), 100, 100);
    widthSlider.setBounds((((getWidth() / 6) * 3) - (100 / 2)), (((getHeight() / 4) * 3) - (100 / 2)), 100, 100);
    freezeModeSlider.setBounds((((getWidth() / 6) * 5) - (100 / 2)), (((getHeight() / 4) * 3) - (100 / 2)), 100, 100);
}
