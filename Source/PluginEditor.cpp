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
    setSize (1100, 385);

    // FONT
    static juce::Typeface::Ptr koratakiFont = juce::Typeface::createSystemTypefaceFor(BinaryData::Korataki_ttf, BinaryData::Korataki_ttfSize);
    juce::LookAndFeel_V4::getDefaultLookAndFeel().setDefaultSansSerifTypeface(koratakiFont);

    // BACKGROUND
    juce::Parallelogram<float> area (getLocalBounds().removeFromTop(355).toFloat());
    pluginName.setText("TEMPEST");
    pluginName.setJustification(juce::Justification::centred);
    pluginName.setBoundingBox(area);
    pluginName.setColour(juce::Colours::darkgrey);
    pluginName.setAlpha(0.15f);
    pluginName.setFontHeight(150.0f);
    addAndMakeVisible(&pluginName);
    
    backgroundArea = getLocalBounds().removeFromTop(355).toFloat();
    background = juce::ImageCache::getFromMemory(BinaryData::_2158a_jpg, BinaryData::_2158a_jpgSize);
    background = background.convertedToFormat(juce::Image::PixelFormat::ARGB);
    background.multiplyAllAlphas(0.4f);

    // DISTORTION
    distortionBypass.setClickingTogglesState(true);
    distortionBypass.setConnectedEdges(3);
    distortionBypass.addListener(this);
    distortionBypass.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour(126, 37, 255));
    addAndMakeVisible(&distortionGui);
    addAndMakeVisible(&distortionBypass);

    // DELAY
    delayBypass.setClickingTogglesState(true);
    delayBypass.setConnectedEdges(3);
    delayBypass.addListener(this);
    delayBypass.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour(24, 98, 255));
    addAndMakeVisible(&delayGui);
    addAndMakeVisible(&delayBypass);

    // REVERB
    reverbBypass.setClickingTogglesState(true);
    reverbBypass.setConnectedEdges(3);
    reverbBypass.addListener(this);
    reverbBypass.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour(0, 174, 255));
    addAndMakeVisible(&reverbGui);
    addAndMakeVisible(&reverbBypass);

    // DISTORTION VARIABLES
    toneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "tone", distortionGui.getToneSlider());
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "gain", distortionGui.getGainSlider());
    distortionMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "distortionMix", distortionGui.getDistortionMixSlider());
    clipButtonsAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getValueTreeState(), "clip", distortionGui.getClipButtons());
    distortionBypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getValueTreeState(), "distortionBypass", distortionBypass);

    // DELAY VARIABLES
    timeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "time", delayGui.getTimeSlider());
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "feedback", delayGui.getFeedbackSlider());
    delayMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "delayMix", delayGui.getDelayMixSlider());
    delayBypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getValueTreeState(), "delayBypass", delayBypass);

    // REVERB VARIABLES
    roomSizeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "roomSize", reverbGui.getRoomSizeSlider());
    dampingSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "damping", reverbGui.getDampingSlider());
    reverbMixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "reverbMix", reverbGui.getReverbMixSlider());
    widthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTreeState(), "width", reverbGui.getWidthSlider());
    reverbBypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getValueTreeState(), "reverbBypass", reverbBypass);
}

GuitarPluginAudioProcessorEditor::~GuitarPluginAudioProcessorEditor()
{
}

//==============================================================================
void GuitarPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
    g.drawImage(background, backgroundArea);
}

void GuitarPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    pluginName.setBounds(0, 0, getWidth(), getHeight());

    distortionGui.setBounds(getWidth() / 3 * 0, 0, getWidth() / 3, getHeight() - 30);
    distortionBypass.setBounds(getWidth() / 3 * 0, getHeight() - 30, getWidth() / 3, 30);
    
    delayGui.setBounds(getWidth() / 3 * 1 + 1, 0, getWidth() / 3, getHeight() - 30);
    delayBypass.setBounds(getWidth() / 3 * 1, getHeight() - 30, getWidth() / 3 + 1, 30);

    reverbGui.setBounds(getWidth() / 3 * 2 + 2, 0, getWidth() / 3, getHeight() - 30);
    reverbBypass.setBounds(getWidth() / 3 * 2 + 1, getHeight() - 30, getWidth() / 3 + 1, 30);
}

void GuitarPluginAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &distortionBypass)
    {
        if (distortionBypass.getToggleState() == false)
        {
            distortionGui.setInterceptsMouseClicks(false, false);
            distortionGui.setAlpha(0.3f);
        }
        else if (distortionBypass.getToggleState() == true)
        {
            distortionGui.setInterceptsMouseClicks(true, true);
            distortionGui.setAlpha(1.0f);
        }
    }
    else if (button == &delayBypass)
    {
        if (delayBypass.getToggleState() == false)
        {
            delayGui.setInterceptsMouseClicks(false, false);
            delayGui.setAlpha(0.3f);
        }
        else if (delayBypass.getToggleState() == true)
        {
            delayGui.setInterceptsMouseClicks(true, true);
            delayGui.setAlpha(1.0f);
        }
    }
    else if (button == &reverbBypass)
    {
        if (reverbBypass.getToggleState() == false)
        {
            reverbGui.setInterceptsMouseClicks(false, false);
            reverbGui.setAlpha(0.3f);
        }
        else if (reverbBypass.getToggleState() == true)
        {
            reverbGui.setInterceptsMouseClicks(true, true);
            reverbGui.setAlpha(1.0f);
        }
    }
}
