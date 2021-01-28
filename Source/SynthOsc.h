/*
  ==============================================================================

    SynthOsc.h
    Created: 10 Jan 2021 10:27:54am
    Author:  richm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

template <typename Type>
class SynthOsc {
private:
    enum {
        oscIndex,
        gainIndex
    };

    juce::dsp::ProcessorChain<juce::dsp::Oscillator<Type>, juce::dsp::Gain<Type>> processorChain;
    //==============================================================================
    void setSine(juce::dsp::Oscillator<Type>& osc);
    void setSquare(juce::dsp::Oscillator<Type>& osc);
    void setTriangle(juce::dsp::Oscillator<Type>& osc);
    void setSawtooth(juce::dsp::Oscillator<Type>& osc);

public:
    SynthOsc();
    void setFrequency(Type frequency);
    void setLevel(Type level);
    template <typename ProcessContext>
    void process(const ProcessContext& context) {
        this->processorChain.process(context);
    };
    void prepare(const juce::dsp::ProcessSpec& spec);
};