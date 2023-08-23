/*
  ==============================================================================

    lfoData.cpp
    Created: 22 Aug 2023 4:40:48pm
    Author:  kylew

  ==============================================================================
*/

#include "lfoData.h"

void lfoData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;

    initialise([](float x) { return std::sin(x); });
    setFrequency(3.f);
    prepare({ spec.sampleRate / lfoUpdateRate, spec.maximumBlockSize, spec.numChannels });
}

float lfoData::processNextBlock(juce::AudioBuffer<float>& buffer)
{
    auto block = juce::dsp::AudioBlock<float>(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    for (int ch = 0; ch < context.getOutputBlock().getNumChannels(); ++ch)
    {
        for (int s = 0; s < context.getOutputBlock().getNumSamples(); ++s)
        {
            auto output = processSample(context.getOutputBlock().getSample(ch, s));
            return output;
            /*auto scale = juce::jmap(output, -1.f, 1.f, 1.f, 10.f);
            DBG("output " << scale);*/
        }
    }
}

void lfoData::setRate(float rate)
{
    setFrequency(rate);
}

void lfoData::modulateADSR(float attack, float decay, float sustain, float release, float output)
{
    auto newAttackParam = juce::jmap(attack, 0.f, 1.f, 0.f, 5.f);
    newAttackParam *= output;
    decay += newAttackParam;
    DBG("attack " << decay);
}

void lfoData::modulatePhaserFilter(float rate, float depth, float centerFrq, float feedback, float mix, float output, std::array<float, 5>& params)
{
    auto newRateParam = juce::jmap(rate, 0.f, 1.f, .1f, 10.f);
    newRateParam *= output;
    params[0] += newRateParam;

    auto newDepthParam = output * depth;
    params[1] += newDepthParam;

    auto newCenterFreqParam = juce::jmap(rate, 0.f, 1.f, 20.f, 20000.f);
    newCenterFreqParam *= output;
    params[2] += newCenterFreqParam;

    auto newFeedbackParam = juce::jmap(rate, 0.f, 1.f, -1.f, 1.f);
    newFeedbackParam *= output;
    params[3] += newFeedbackParam;

    auto newMixParam = output * mix;
    params[4] += newMixParam;

}
