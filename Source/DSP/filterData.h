/*
  ==============================================================================

    filterData.h
    Created: 8 Aug 2023 4:49:11pm
    Author:  kylew

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct FilterData 
{
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateLadderParams(int mode, float cuttoffFreq, float resonance, float drive);
    void updatePhaserParams(float rate, float depth, float centerFreq, float feedback, float mix);
    void processComb(int channel, juce::AudioBuffer<float>& buffer, float freq, float feedback, float gain, float mix, double sampleRate);
    void reset(int filterChoice);
    
private:
    juce::dsp::LadderFilter<float> ladderFilter;
    juce::dsp::Phaser<float> phaserFilter;
    std::array<juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear>, 2> combFilter;
    std::array<juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear>, 2> smoothedDelay;
};