/*
  ==============================================================================

    lfoData.h
    Created: 22 Aug 2023 4:40:48pm
    Author:  kylew

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct lfoData : public juce::dsp::Oscillator<float>
{
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    float processNextBlock(juce::AudioBuffer<float>& buffer);
    void setWaveType(std::array<bool, 4>&);
    void setRate(float rate);
    void modulateADSR(float attack, float decay, float sustain, float release, float gain, float output, std::array<float, 5>&);
    void modulateLadderFilter(float cutoff, float resonance, float drive, float output, std::array<float, 3>&);
    void modulatePhaserFilter(float rate, float depth, float centerFrq, float feedback, float mix, float output, std::array<float, 5>&);
    void modulateCombFilter(float freq, float feedback, float gain, float mix, float output, std::array<float, 4>&);

private:

    int lfoUpdateRate = 100;
};