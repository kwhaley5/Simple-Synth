/*
  ==============================================================================

    adsrData.cpp
    Created: 2 Aug 2023 2:31:49pm
    Author:  kylew

  ==============================================================================
*/

#include "oscData.h"
#include "../PluginProcessor.h"

void oscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    prepare(spec);
    oscGain.prepare(spec);
    oscGain.setGainLinear(.1f);
}

void oscData::setWaveType(std::array<bool, 4>& array)
{
    if (array[0])
        initialise([] (float x) { return std::sin(x); });
    else if(array[1])
        initialise([](float x) { return x / juce::MathConstants<float>::pi; });
    else if (array[2])
        initialise([](float x) { return x < 0.0f ? -1.f : 1.f; });
    else
        initialise([](float x) { return std::asin(std::cos(x)) / juce::MathConstants<float>::halfPi; });
}

void oscData::setWaveFreq(int midiNoteNumber, int osc1MidiNoteNumber, bool isFmActive, float depth)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    if (isFmActive)
    {
        setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + (juce::MidiMessage::getMidiNoteInHertz(osc1MidiNoteNumber) * depth));
    };
}

void oscData::processNextBlock(juce::dsp::ProcessContextReplacing<float>& context)
{
    process(context);
    oscGain.process(context);
}

void oscData::setGain(float gain)
{
    oscGain.setGainDecibels(gain);
}

void adsrData::setADSR(float attack, float decay, float sustain, float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    setParameters(adsrParams);
}
