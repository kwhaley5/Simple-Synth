/*
  ==============================================================================

    globalGain.h
    Created: 17 Aug 2023 9:33:52am
    Author:  kylew

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct GlobalGain : public juce::dsp::Gain<float>
{
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void setGain(float gain);
    void processCtx(juce::AudioBuffer<float>& buffer);
};