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
    oscData();
    ~oscData();

    void setWaveType(std::array<bool, 4>&);
};

struct adsrData : public juce::ADSR 
{
    void setADSR(float attack, float decay, float sustain, float release);
    
private:

    juce::ADSR::Parameters adsrParams;
};