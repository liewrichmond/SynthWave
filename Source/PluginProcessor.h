/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"
#include "SynthOsc.h"
#include "WavySynth.h"


//==============================================================================
/**
*/
class SynthWaveAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SynthWaveAudioProcessor();
    ~SynthWaveAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:

    juce::AudioProcessorValueTreeState::ParameterLayout createParamLayout();
    juce::dsp::Reverb::Parameters createReverbParams();

    WavySynth synth;
    juce::AudioProcessorValueTreeState parameters;
    
    //ADSR params
    std::atomic<float>* attack = nullptr;
    std::atomic<float>* decay = nullptr;
    std::atomic<float>* sustain = nullptr;
    std::atomic<float>* release = nullptr;

    //Reverb params
    std::atomic<float>* roomSize = nullptr;
    std::atomic<float>* damping = nullptr;
    std::atomic<float>* wetLevel = nullptr;
    std::atomic<float>* dryLevel = nullptr;
    std::atomic<float>* reverbWidth = nullptr;
    std::atomic<float>* freezeMode = nullptr;

    //Gain Param
    std::atomic<float>* gain = nullptr;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthWaveAudioProcessor)
};
