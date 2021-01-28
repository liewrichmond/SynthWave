/*
  ==============================================================================

    RotarySlider.cpp
    Created: 14 Jan 2021 11:17:42am
    Author:  richm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RotarySlider.h"

//==============================================================================
RotarySlider::RotarySlider(const char* labelText, const char* praramId, juce::AudioProcessorValueTreeState& state) :
    valueTree(state)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    this->label.setText(labelText, juce::dontSendNotification);
    addAndMakeVisible(this->label);
    this->slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    addAndMakeVisible(this->slider);
    this->attachment.reset(new SliderAttachment(valueTree, praramId, this->slider));
}

RotarySlider::~RotarySlider()
{
}

void RotarySlider::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    //g.setColour (juce::Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("RotarySlider", getLocalBounds(),
    //            juce::Justification::centred, true);   // draw some placeholder text
}


void RotarySlider::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const int marginTop = 5;
    const int padding = 5;
    const int sideMargin = 5;

    const auto topLeft = this->getBounds().getTopLeft();
    const int xPos = topLeft.getX();
    const int yPos = topLeft.getY();

    const int componentHeight = this->getLocalBounds().getHeight();
    const int componentWidth = this->getLocalBounds().getWidth();
    const int labelHeight = 15;
    const int textBoxHeight = 15;
    const int sliderHeight = componentHeight - labelHeight - textBoxHeight;

    this->label.setBounds(0, 0, componentWidth - 2 * sideMargin, labelHeight);
    this->label.setCentreRelative(0.7f, 0.1f);
    this->slider.setBounds(0 + sideMargin, 0 + labelHeight + padding, componentWidth - 2*sideMargin, sliderHeight);
    this->slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, componentWidth - 2*sideMargin, textBoxHeight);
}
