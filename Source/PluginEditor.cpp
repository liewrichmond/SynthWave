/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthWaveAudioProcessorEditor::SynthWaveAudioProcessorEditor (SynthWaveAudioProcessor& p, juce::AudioProcessorValueTreeState& state)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTree(state), adsrEditor(state), reverbEditor(state)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    //addAndMakeVisible(subcomponents)
    addAndMakeVisible(adsrEditor);
    addAndMakeVisible(reverbEditor);

    addAndMakeVisible(this->slider);
    this->slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    this->attachment.reset(new SliderAttachment(valueTree, "gainLevel", this->slider));
    setSize (800, 300);
}

SynthWaveAudioProcessorEditor::~SynthWaveAudioProcessorEditor()
{
}

//==============================================================================
void SynthWaveAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    //g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    //g.setColour(juce::Colours::grey);
    //g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour(juce::Colours::white);
    //g.setFont(14.0f);
    //g.drawText("ADSREditor", getLocalBounds(),
    //    juce::Justification::centred, true);   // draw some placeholder text

    //this->adsrEditor.paint(g);
}

void SynthWaveAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    adsrEditor.setBounds(20, 20, 200, 200);
    reverbEditor.setBounds(250, 20, 300, 200);
    slider.setBounds(600, 20, 40, 200);
}
