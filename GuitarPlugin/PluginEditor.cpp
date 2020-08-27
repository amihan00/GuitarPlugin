/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GuitarPluginAudioProcessorEditor::GuitarPluginAudioProcessorEditor (GuitarPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 500);

    addAndMakeVisible(&distortionGui);
    addAndMakeVisible(&distortionBypass);

    addAndMakeVisible(&delayGui);
    addAndMakeVisible(&delayBypass);

    addAndMakeVisible(&reverbGui);
    addAndMakeVisible(&reverbBypass);

    // DISTORTION VARIABLES
    toneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "tone", distortionGui.getToneSlider());
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "gain", distortionGui.getGainSlider());
    distortionMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "distortionMix", distortionGui.getDistortionMixSlider());
    clipMenuAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.getValueTreeState(), "clip", distortionGui.getClipMenu());
    distortionBypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getValueTreeState(), "distortionBypass", distortionGui.getDistortionBypassButton());

    // DELAY VARIABLES
    timeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "time", delayGui.getTimeSlider());
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "feedback", delayGui.getFeedbackSlider());
    delayMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "delayMix", delayGui.getDelayMixSlider());
    delayBypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getValueTreeState(), "delayBypass", delayGui.getDelayBypassButton());

    // REVERB VARIABLES
    roomSizeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "roomSize", reverbGui.getRoomSizeSlider());
    dampingSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "damping", reverbGui.getDampingSlider());
    reverbMixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "reverbMix", reverbGui.getReverbMixSlider());
    widthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "width", reverbGui.getWidthSlider());
    reverbBypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getValueTreeState(), "reverbBypass", reverbGui.getReverbBypassButton());
}

GuitarPluginAudioProcessorEditor::~GuitarPluginAudioProcessorEditor()
{
}

//==============================================================================
void GuitarPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //juce::ImageConvolutionKernel blur(15);
    //blur.createGaussianBlur(7.0f);

    //juce::File backgroundImage = "C:/storm.jpg";
    //juce::Image background = juce::ImageCache::getFromFile(backgroundImage);
    //juce::Image blurredBackground = background.createCopy();

    //juce::Rectangle<int> blurArea(0, 0, getWidth() * 2, getHeight() - 50);
    //blur.applyToImage(blurredBackground, background, blurArea);

    //g.drawImage(blurredBackground, getLocalBounds().toFloat());
}

void GuitarPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    distortionGui.setBounds(getWidth() / 3 * 0, 0, getWidth() / 3, getHeight() / 2);
    distortionBypass.setBounds(getWidth() / 3 * 0, getHeight() / 2, 50, 50);

    delayGui.setBounds(getWidth() / 3 * 1 + 1, 0, getWidth() / 3, getHeight() / 2);
    delayBypass.setBounds(getWidth() / 3 * 1, getHeight() / 2, 50, 50);

    reverbGui.setBounds(getWidth() / 3 * 2 + 2, 0, getWidth() / 3, getHeight() / 2);
    reverbBypass.setBounds(getWidth() / 3 * 2, getHeight() / 2, 50, 50);
}
