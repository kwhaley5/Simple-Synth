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
    void setFmParams(float freq, float depth, std::array<bool, 4>& array);
    void setGain(float gain);

private:
    juce::dsp::Oscillator<float> fmOsc{ ([](float x) { return std::sin(x); }) };
    juce::dsp::Gain<float> oscGain;
    float fmMod{ 0.f };
    float fmDepth{ 0.f };
    int lastMidiNote{ 0 };
};

struct adsrData : public juce::ADSR 
{
    void setADSR(float attack, float decay, float sustain, float release);
    
private:

    juce::ADSR::Parameters adsrParams;
};