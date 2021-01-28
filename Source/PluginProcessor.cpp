/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthWaveAudioProcessor::SynthWaveAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    parameters(*this, nullptr, juce::Identifier("ProcessorParams"), createParamLayout())
#endif
{
    this->synth.setNumVoices(5);

    this->attack = parameters.getRawParameterValue("attack");
    this->decay = parameters.getRawParameterValue("attack");
    this->sustain = parameters.getRawParameterValue("sustain");
    this->release = parameters.getRawParameterValue("release");

    this->roomSize = parameters.getRawParameterValue("roomSize");
    this->damping = parameters.getRawParameterValue("damping");
    this->wetLevel = parameters.getRawParameterValue("wetLevel");
    this->dryLevel = parameters.getRawParameterValue("dryLevel");
    this->reverbWidth = parameters.getRawParameterValue("reverbWidth");
    this->freezeMode = parameters.getRawParameterValue("freezeMode");

    this->gain = parameters.getRawParameterValue("gainLevel");
}

SynthWaveAudioProcessor::~SynthWaveAudioProcessor()
{
}

//==============================================================================
const juce::String SynthWaveAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthWaveAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthWaveAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthWaveAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthWaveAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthWaveAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthWaveAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthWaveAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthWaveAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthWaveAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthWaveAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    this->synth.prepare({ sampleRate, (juce::uint32)samplesPerBlock, 2 });
}

void SynthWaveAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthWaveAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthWaveAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    buffer.clear();
    this->synth.setEvenlopeParams({ *attack, *decay, *sustain, *release});
    /*this->synth.setReverbParams({*roomSize, *damping, *wetLevel, *dryLevel, *reverbWidth, *freezeMode });*/
    this->synth.setReverbParams(this->createReverbParams());
    this->synth.setGain(*gain);
    this->synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SynthWaveAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthWaveAudioProcessor::createEditor()
{
    return new SynthWaveAudioProcessorEditor (*this, this->parameters);
}

//==============================================================================
void SynthWaveAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthWaveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}
//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout SynthWaveAudioProcessor::createParamLayout() {
    return 
    {
        std::make_unique<juce::AudioParameterFloat>("attack", "Attack", 0.01f, 5.0f, 0.3f),
        std::make_unique<juce::AudioParameterFloat>("decay", "Decay", 0.01f, 2.0f, 0.3f),
        std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", 0.01f, 1.0f, 1.0f),
        std::make_unique<juce::AudioParameterFloat>("release", "Release", 0.01f, 5.0f, 0.3f),

        std::make_unique<juce::AudioParameterFloat>("roomSize", "RoomSize", 0.0f, 1.0f, 0.5f),
        std::make_unique<juce::AudioParameterFloat>("damping", "Damping", 0.0f, 1.0f, 0.5f),
        std::make_unique<juce::AudioParameterFloat>("wetLevel", "WetLevel", 0.0f, 1.0f, 0.33f),
        std::make_unique<juce::AudioParameterFloat>("dryLevel", "DryLevel", 0.0f, 1.0f, 0.4f),
        std::make_unique<juce::AudioParameterFloat>("reverbWidth", "Width", 0.0f, 1.0f, 1.0f),
        std::make_unique<juce::AudioParameterBool>("freezeMode", "FreezeMode", false),

        std::make_unique<juce::AudioParameterFloat>("gainLevel", "GainLevel", 0.0f, 18.0f, 0.7f)
    };
}

juce::dsp::Reverb::Parameters SynthWaveAudioProcessor::createReverbParams()
{
    auto freezeModeVal = 0.48f;
    if (*freezeMode) {
        std::cout << "Freeze Mode ON \n";
        freezeModeVal = 0.79;
    }
    return { *roomSize, *damping, *wetLevel, *dryLevel, *reverbWidth, freezeModeVal };
   
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthWaveAudioProcessor();
}
