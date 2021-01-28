/*
  ==============================================================================

    WavySynth.cpp
    Created: 11 Jan 2021 10:39:08am
    Author:  richm

  ==============================================================================
*/

#include "WavySynth.h"

WavySynth::WavySynth()
{
    this->setNumVoices(1);
    this->addSound(new SynthSound());
}

void WavySynth::renderNextBlock(juce::AudioBuffer<float>& outputAudio, const juce::MidiBuffer& inputMidi, int startSample, int numSamples)
{
    juce::Synthesiser::renderNextBlock(outputAudio, inputMidi, startSample, numSamples);

    auto block = juce::dsp::AudioBlock<float>{ outputAudio };
    auto subBlock = block.getSubBlock((size_t)startSample, (size_t)numSamples);
    auto context = juce::dsp::ProcessContextReplacing<float>(subBlock);

    this->fxChain.process(context);
}

void WavySynth::prepare(juce::dsp::ProcessSpec spec)
{
    juce::Synthesiser::setCurrentPlaybackSampleRate(spec.sampleRate);

    for (auto* voice : this->voices) {
        dynamic_cast<SynthVoice*>(voice)->prepare(spec);
    }

    this->fxChain.prepare(spec);
}

void WavySynth::setNumVoices(int numVoices)
{
    for (auto i = 0; i < (size_t)numVoices; ++i) {
        this->addVoice(new SynthVoice());
    }
}

void WavySynth::setEvenlopeParams(const juce::ADSR::Parameters params)
{
    for (auto* voice : this->voices) {
        dynamic_cast<SynthVoice*>(voice)->setEnvelopeParams(params);
    }
}

void WavySynth::setReverbParams(const juce::dsp::Reverb::Parameters params)
{
    auto& reverb = this->fxChain.get<this->reverbIndex>();
    reverb.setParameters(params);
}

void WavySynth::setGain(float newGain)
{
    for (auto* voice : this->voices) {
        dynamic_cast<SynthVoice*>(voice)->setGain(newGain);
    }
}

