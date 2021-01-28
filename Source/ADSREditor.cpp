/*
  ==============================================================================

    ADSREditor.cpp
    Created: 14 Jan 2021 10:09:07am
    Author:  richm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSREditor.h"

//==============================================================================
ADSREditor::ADSREditor(juce::AudioProcessorValueTreeState& state) :
    valueTree(state), attackSlider("Attack", "attack", state), decaySlider("Decay", "decay", state), sustainSlider("Sustain", "sustain", state), releaseSlider("Release", "release", state)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
}

ADSREditor::~ADSREditor()
{
}

void ADSREditor::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void ADSREditor::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const int componentWidth = this->getLocalBounds().getWidth();
    const int componentHeight = this->getLocalBounds().getHeight();

    this->attackSlider.setBounds(0, 0, componentWidth / 2, componentHeight / 2);
    this->decaySlider.setBounds(0, componentHeight / 2, componentWidth / 2, componentHeight / 2);
    this->sustainSlider.setBounds(componentWidth / 2, 0, componentWidth / 2, componentHeight / 2);
    this->releaseSlider.setBounds(componentWidth / 2, componentHeight / 2, componentWidth / 2, componentHeight / 2);
}
