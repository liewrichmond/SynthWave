/*
  ==============================================================================

    WavySynth.h
    Created: 11 Jan 2021 10:39:08am
    Author:  richm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "./SynthVoice.h"
#include "./SynthSound.h"

class WavySynth : juce::Synthesiser {
public:
    WavySynth();
    void renderNextBlock(juce::AudioBuffer<float>& outputAudio,
        const juce::MidiBuffer& inputMidi,
        int startSample,
        int numSamples);
    void prepare(juce::dsp::ProcessSpec spec);
    void setNumVoices(int numVoices);
    void setEvenlopeParams(const juce::ADSR::Parameters params);
    void setReverbParams(const juce::dsp::Reverb::Parameters params);
    void setGain(float newGain);

private:
    enum {
        reverbIndex
    };

    juce::dsp::ProcessorChain<juce::dsp::Reverb> fxChain;
};