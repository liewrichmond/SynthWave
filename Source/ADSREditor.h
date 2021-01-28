/*
  ==============================================================================

    ADSREditor.h
    Created: 14 Jan 2021 10:09:07am
    Author:  richm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "./RotarySlider.h"
typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
/*
*/
class ADSREditor  : public juce::Component
{
public:
    ADSREditor(juce::AudioProcessorValueTreeState& state);
    ~ADSREditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::AudioProcessorValueTreeState& valueTree;
    RotarySlider attackSlider;
    RotarySlider decaySlider;
    RotarySlider sustainSlider;
    RotarySlider releaseSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSREditor)
};
