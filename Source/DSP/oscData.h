/*
  ==============================================================================

    adsrData.h
    Created: 2 Aug 2023 2:31:49pm
    Author:  kylew

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct oscData : public juce::dsp::Oscillator<float>
{
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(std::array<bool, 4>&);
    void setWaveFreq(int midiNoteNumber, int osc1MidiNoteNumber, bool isFmActive, float depth);
    void processNextBlock(juce::dsp::ProcessContextReplacing<float>&);
    void setGain(float gain);

private:
    juce::dsp::Gain<float> oscGain;
};

struct adsrData : public juce::ADSR 
{
    void setADSR(float attack, float decay, float sustain, float release);
    
private:

    juce::ADSR::Parameters adsrParams;
};