/*
  ==============================================================================

    SynthOsc.cpp
    Created: 10 Jan 2021 10:27:54am
    Author:  richm

  ==============================================================================
*/

#include "SynthOsc.h"

template <typename Type>
SynthOsc<Type>::SynthOsc() {
    auto& osc = this->processorChain.template get<this->oscIndex>();
    this->setTriangle(osc);
};

template <typename Type>
void SynthOsc<Type>::setSine(juce::dsp::Oscillator<Type>& osc) {
    osc.initialise([](Type x) {
        return std::sin(x); }, 128);
};

template <typename Type>
void SynthOsc<Type>::setSquare(juce::dsp::Oscillator<Type>& osc) {
    osc.initialise([](Type x) {
        if (x <= 0) {
            return 1;
        }
        else {
            return 0;
        }
        }, 128);
};

template <typename Type>
void SynthOsc<Type>::setTriangle(juce::dsp::Oscillator<Type>& osc) {
    osc.initialise([](Type x) {
        if (x == 1) {
            return (Type)1;
        }
        else if (x < 0) {
            return ((1 / (Type)juce::MathConstants<double>::pi * x) + 1);
        }
        else {
            return ((-1 / (Type)juce::MathConstants<double>::pi * x) + 1);
        }
        }, 128);
};

template <typename Type>
void SynthOsc<Type>::setSawtooth(juce::dsp::Oscillator<Type>& osc) {
    osc.initialise([](Type x) {
        return  juce::jmap(
            x,
            Type(-juce::MathConstants<double>::pi),
            Type(juce::MathConstants<double>::pi),
            Type(-1),
            Type(1)); }, 2);
};

template<typename Type>
void SynthOsc<Type>::prepare(const juce::dsp::ProcessSpec& spec) {
    this->processorChain.prepare(spec);
};

template<typename Type>
void SynthOsc<Type>::setFrequency(Type frequency) {
    auto& osc = this->processorChain.template get<this->oscIndex>();
    osc.setFrequency(frequency, true);
};

template<typename Type>
void SynthOsc<Type>::setLevel(Type level) {
    auto& gain = this->processorChain.template get<this->gainIndex>();
    gain.setGainLinear(level);
};

template class SynthOsc<float>;
template class SynthOsc<double>;