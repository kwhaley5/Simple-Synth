/*
  ==============================================================================

    globalGain.cpp
    Created: 17 Aug 2023 9:33:52am
    Author:  kylew

  ==============================================================================
*/

#include "globalGain.h"

void GlobalGain::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    reset();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    prepare(spec);
    setRampDurationSeconds(.05);
}

void GlobalGain::setGain(float gain)
{
    setGainDecibels(gain);
}

void GlobalGain::processCtx(juce::AudioBuffer<float>& buffer)
{
    auto block = juce::dsp::AudioBlock<float>(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    process(context);
}
