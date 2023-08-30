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
    fmOsc.prepare(spec);
    oscGain.prepare(spec);
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
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
    lastMidiNote = midiNoteNumber;
}

void oscData::processNextBlock(juce::dsp::ProcessContextReplacing<float>& context)
{
    for (int ch = 0; ch < context.getOutputBlock().getNumChannels(); ++ch)
    {
        for (int s = 0; s < context.getOutputBlock().getNumSamples(); ++s)
        {
            fmMod = fmOsc.processSample(context.getOutputBlock().getSample(ch, s)) * fmDepth;
        }
    }

    process(context);
    oscGain.process(context);
}

void oscData::setFmParams(float freq, float depth, bool isOn, std::array<bool, 4>& array)
{
    if (array[0])
        fmOsc.initialise([](float x) { return std::sin(x); });
    else if (array[1])
        fmOsc.initialise([](float x) { return x / juce::MathConstants<float>::pi; });
    else if (array[2])
        fmOsc.initialise([](float x) { return x < 0.0f ? -1.f : 1.f; });
    else
        fmOsc.initialise([](float x) { return std::asin(std::cos(x)) / juce::MathConstants<float>::halfPi; });

    if (isOn)
    {
        fmOsc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(freq));
        fmDepth = depth;
        auto currentFreq = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod;
        setFrequency(currentFreq >= 0 ? currentFreq : currentFreq * -1.0f);
    }
    else
    {
        fmOsc.reset();
        fmDepth = 0;
        auto currentFreq = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote);
        setFrequency(currentFreq >= 0 ? currentFreq : currentFreq * -1.0f);
    }
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
