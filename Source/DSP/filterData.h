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
    void reset();
    
private:
    juce::dsp::LadderFilter<float> ladderFilter;
    juce::dsp::Phaser<float> phaserFilter;
};