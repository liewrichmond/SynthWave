/*
  ==============================================================================

    SynthSound.h
    Created: 7 Jan 2021 3:10:49pm
    Author:  richm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {
    // Inherited via SynthesiserSound
    virtual bool appliesToNote(int midiNoteNumber) override {
        return true;
    };
    virtual bool appliesToChannel(int midiChannel) override {
        return true;
    };
};