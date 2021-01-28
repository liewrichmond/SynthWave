/*
  ==============================================================================

    ReverbEditor.h
    Created: 14 Jan 2021 11:10:06pm
    Author:  richm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "./RotarySlider.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

//==============================================================================
/*
*/
class ReverbEditor  : public juce::Component
{
public:
    ReverbEditor(juce::AudioProcessorValueTreeState&  state);
    ~ReverbEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::AudioProcessorValueTreeState& valueTree;
    
    RotarySlider roomSizeSlider;
    RotarySlider dampingSlider;
    RotarySlider wetLevelSlider;
    RotarySlider dryLevelSlider;
    RotarySlider reverbWidthSlider;
    RotarySlider freezeModeSlider;

    juce::TextButton toggleButton;
    std::unique_ptr<ButtonAttachment> toggleAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbEditor)
};
