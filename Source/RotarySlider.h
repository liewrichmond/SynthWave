/*
  ==============================================================================

    RotarySlider.h
    Created: 14 Jan 2021 11:17:42am
    Author:  richm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
//==============================================================================
/*
*/
class RotarySlider  : public juce::Component
{
public:
    RotarySlider(const char* label, const char* praramId, juce::AudioProcessorValueTreeState& state);
    ~RotarySlider() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::AudioProcessorValueTreeState& valueTree;

    juce::Label label;
    juce::Slider slider;
    std::unique_ptr<SliderAttachment> attachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotarySlider)
};
