/*
  ==============================================================================

    SynthVoice.h
    Created: 7 Jan 2021 3:10:40pm
    Author:  richm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "./libs/Maximilian/src/maximilian.h"
#include "SynthOsc.h"

class SynthVoice : public juce::SynthesiserVoice {
public:

    SynthVoice() {
        auto& gain = this->processorChain.get<this->gainIndex>();
        gain.setGainLinear(1.0f);
        gain.setRampDurationSeconds(0.1f);

        auto& filter = this->processorChain.get<this->filterIndex>();
        filter.setCutoffFrequencyHz(1000.0f);
        filter.setResonance(0.7f);
    }

    void setEnvelopeParams(const juce::ADSR::Parameters params) {
        this->envelope.setParameters(params);
    }

    // Processor Chain stuff
    void prepare(const juce::dsp::ProcessSpec& spec) {
        this->tempBuffer.setSize(spec.numChannels, spec.maximumBlockSize, true, true, true);
        this->tempBlock = juce::dsp::AudioBlock<float>(tempBuffer);
        this->processorChain.prepare(spec);
        this->envelope.setSampleRate(spec.sampleRate);
    }

    // Inherited via SynthesiserVoice
    bool canPlaySound(juce::SynthesiserSound* sound) {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    };

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override {
        float freqInHz = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        this->setVoiceFrequency(freqInHz);
        this->setVoiceLevel(velocity);
        this->envelope.noteOn();
    };

    void stopNote(float velocity, bool allowTailOff) override {
        this->envelope.noteOff();
        this->clearCurrentNote();
    };

    void pitchWheelMoved(int newPitchWheelValue) override {};

    void controllerMoved(int controllerNumber, int newControllerValue) override {};

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override {
        auto audioBlock = this->tempBlock.getSubBlock((size_t)startSample, (size_t)numSamples);
        audioBlock.clear();
        
        juce::dsp::ProcessContextReplacing<float> context(audioBlock);

        this->processorChain.process(context);

        this->envelope.applyEnvelopeToBuffer(tempBuffer, startSample, numSamples);

        juce::dsp::AudioBlock<float>(outputBuffer)
            .getSubBlock((size_t)startSample, (size_t)numSamples)
            .add(audioBlock);
    };

    void setGain(float newGain) {
        auto& gain = this->processorChain.get<this->gainIndex>();
        gain.setGainLinear(newGain);
    };

private:
    void setVoiceFrequency(float frequency) {
        this->processorChain.get<this->mainOscillator>().setFrequency(frequency);
        this->processorChain.get<this->freqDownOscillator>().setFrequency(0.99f * frequency);
        this->processorChain.get<this->freqUpOscillator>().setFrequency(1.01f * frequency);
    };

    void setVoiceLevel(float level) {
        this->processorChain.get<this->mainOscillator>().setLevel(level);
        this->processorChain.get<this->freqDownOscillator>().setLevel(level);
        this->processorChain.get<this->freqUpOscillator>().setLevel(level);
    };

    enum {
        mainOscillator,
        freqUpOscillator,
        freqDownOscillator,
        filterIndex,
        gainIndex
    };

    juce::HeapBlock<char> heapBlock;
    juce::dsp::AudioBlock<float> tempBlock;
    juce::AudioBuffer<float> tempBuffer;
    juce::ADSR envelope;

    juce::dsp::ProcessorChain<SynthOsc<float>, SynthOsc<float>, SynthOsc<float>, juce::dsp::LadderFilter<float>, juce::dsp::Gain<float>> processorChain;   
};