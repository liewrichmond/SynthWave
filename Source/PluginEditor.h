/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ADSREditor.h"
#include "ReverbEditor.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;


//==============================================================================
/**
*/
class SynthWaveAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthWaveAudioProcessorEditor (SynthWaveAudioProcessor&, juce::AudioProcessorValueTreeState& state);
    ~SynthWaveAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    ADSREditor adsrEditor;
    ReverbEditor reverbEditor;

    juce::Slider slider;
    std::unique_ptr<SliderAttachment> attachment;


    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthWaveAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& valueTree;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthWaveAudioProcessorEditor)
};
