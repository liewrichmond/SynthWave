/*
  ==============================================================================

    ReverbEditor.cpp
    Created: 14 Jan 2021 11:10:06pm
    Author:  richm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbEditor.h"

//==============================================================================
ReverbEditor::ReverbEditor(juce::AudioProcessorValueTreeState& state) :
    valueTree(state), roomSizeSlider("Size", "roomSize", state), dampingSlider("Damping", "damping", state), wetLevelSlider("Wet", "wetLevel", state), dryLevelSlider("Dry", "dryLevel", state), reverbWidthSlider("Width", "reverbWidth", state), freezeModeSlider("freeze", "freezeMode", state)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(roomSizeSlider);
    addAndMakeVisible(dampingSlider);
    addAndMakeVisible(wetLevelSlider);
    addAndMakeVisible(dryLevelSlider);
    addAndMakeVisible(reverbWidthSlider);
    addAndMakeVisible(freezeModeSlider);
    //addAndMakeVisible(toggleButton);
    //
    //toggleButton.setButtonText("sup Hoes");
    //this->toggleAttachment.reset(new ButtonAttachment(this->valueTree, "freezeMode", this->toggleButton));
}

ReverbEditor::~ReverbEditor()
{
}

void ReverbEditor::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("ReverbEditor", getLocalBounds(),
    //            juce::Justification::centred, true);   // draw some placeholder text
}

void ReverbEditor::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const int componentWidth = this->getLocalBounds().getWidth();
    const int componentHeight = this->getLocalBounds().getHeight();
    const int nRows = 2;
    const int nCols = 3;
    const int sliderWidth = componentWidth / nCols;
    const int sliderHeight = componentHeight / nRows;

    this->roomSizeSlider.setBounds(0, 0, sliderWidth, sliderHeight);
    this->dampingSlider.setBounds(1*sliderWidth, 0, sliderWidth, sliderHeight);
    this->wetLevelSlider.setBounds(2*sliderWidth, 0, sliderWidth, sliderHeight);
    this->dryLevelSlider.setBounds(0, 1*sliderHeight, sliderWidth, sliderHeight);
    this->reverbWidthSlider.setBounds(1*sliderWidth, 1*sliderHeight,sliderWidth, sliderHeight);
    /*this->freezeModeSlider.setBounds(2*sliderWidth, 1*sliderHeight, sliderWidth, sliderHeight);*/
    //this->toggleButton.setBounds(2 * sliderWidth, 1 * sliderHeight, 100, 50);
    //juce::TextButton& tmp = this->toggleButton;
    //this->toggleButton.onClick = [&tmp]() {
    //    tmp.setToggleState(!tmp.getToggleState(), juce::NotificationType::dontSendNotification);
    //};
}
