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

    newOutput.reset(sampleRate, .005);
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
        }
    }
}

void lfoData::setWaveType(std::array<bool, 4>& array)
{
    if (array[0])
        initialise([](float x) { return std::sin(x); });
    else if (array[1])
        initialise([](float x) { return x / juce::MathConstants<float>::pi; });
    else if (array[2])
        initialise([](float x) { return x < 0.0f ? -1.f : 1.f; });
    else
        initialise([](float x) { return std::asin(std::cos(x)) / juce::MathConstants<float>::halfPi; });
}

void lfoData::setRate(float rate)
{
    setFrequency(rate);
}

void lfoData::modulateADSR(float attack, float decay, float sustain, float release, float gain, float output, std::array<float, 5>& params)
{
    newOutput.setTargetValue(output);

    auto newAttackParam = juce::jmap(attack, 0.f, 1.f, 0.f, 5.f);
    newAttackParam *= newOutput.getNextValue();
    params[0] += newAttackParam;
    params[0] = std::fmin(std::fmax(params[0], 0), 5);

    auto neweDecayParam = juce::jmap(decay, 0.f, 1.f, 0.f, 5.f);
    neweDecayParam *= newOutput.getNextValue();
    params[1] += neweDecayParam;
    params[1] = std::fmin(std::fmax(params[1], 0), 5);

    auto newSustainParam = newOutput.getNextValue() * sustain;
    params[2] += newSustainParam;
    params[2] = std::fmin(std::fmax(params[2], 0), 1);

    auto newReleaseParam = juce::jmap(release, 0.f, 1.f, 0.f, 5.f);
    newReleaseParam *= newOutput.getNextValue();
    params[3] += newReleaseParam;
    params[3] = std::fmin(std::fmax(params[3], 0), 5);

    auto newGainParam = juce::jmap(gain, 0.f, 1.f, 0.f, 72.f);
    newGainParam *= newOutput.getNextValue();
    params[4] += newGainParam;
    params[4] = std::fmin(std::fmax(params[4], -60), 6);


}

void lfoData::modulateLadderFilter(float cutoff, float resonance, float drive, float output, std::array<float, 3>& params)
{
    newOutput.setTargetValue(output);

    auto newCuttoffParam = juce::jmap(cutoff, 0.f, 1.f, 0.f, 19990.f);
    newCuttoffParam *= newOutput.getNextValue();
    params[0] += newCuttoffParam;
    params[0] = std::fmin(std::fmax(params[0], 20), 20000);

    auto newResParam = newOutput.getNextValue() * resonance;
    params[1] += newResParam;
    params[1] = std::fmin(std::fmax(params[1], 0), 1);

    auto newDriveParam = juce::jmap(drive, 0.f, 1.f, 0.f, 9.f);
    newDriveParam *= newOutput.getNextValue();
    params[2] += newDriveParam;
    params[2] = std::fmin(std::fmax(params[2], 1), 10);
}

void lfoData::modulatePhaserFilter(float rate, float depth, float centerFrq, float feedback, float mix, float output, std::array<float, 5>& params)
{
    newOutput.setTargetValue(output);

    auto newRateParam = juce::jmap(rate, 0.f, 1.f, 0.f, 10.f);
    newRateParam *= newOutput.getNextValue();
    params[0] += newRateParam;
    params[0] = std::fmin(std::fmax(params[0], 0), 10);

    auto newDepthParam = newOutput.getNextValue() * depth;
    params[1] += newDepthParam;
    params[1] = std::fmin(std::fmax(params[1], 0), 1);

    auto newCenterFreqParam = juce::jmap(centerFrq, 0.f, 1.f, 0.f, 19990.f);
    newCenterFreqParam *= newOutput.getNextValue();
    params[2] += newCenterFreqParam;
    params[2] = std::fmin(std::fmax(params[2], 20), 20000);

    auto newFeedbackParam = juce::jmap(feedback, 0.f, 1.f, 0.f, 2.f);
    newFeedbackParam *= newOutput.getNextValue();
    params[3] += newFeedbackParam;
    params[3] = std::fmin(std::fmax(params[3], -1), 1);

    auto newMixParam = newOutput.getNextValue() * mix;
    params[4] += newMixParam;
    params[4] = std::fmin(std::fmax(params[4], 0), 1);

}

void lfoData::modulateCombFilter(float freq, float feedback, float gain, float mix, float output, std::array<float, 4>& params)
{
    newOutput.setTargetValue(output);

    auto newFreqParam = juce::jmap(freq, 0.f, 1.f, 0.f, 75.f);
    newFreqParam *= newOutput.getNextValue();
    params[0] += newFreqParam;
    params[0] = std::fmin(std::fmax(params[0], 1), 75);

    auto newFeedbackParm = juce::jmap(feedback, 0.f, 1.f, 0.f, .75f);
    newFeedbackParm *= newOutput.getNextValue();
    params[1] += newFeedbackParm;
    params[1] = std::fmin(std::fmax(params[1], .3), .75);

    auto newGainParam = juce::jmap(gain, 0.f, 1.f, 0.f, 5.f);
    newGainParam *= newOutput.getNextValue();
    params[2] += newGainParam;
    params[2] = std::fmin(std::fmax(params[2], 0), 5);

    auto newMixParam = newOutput.getNextValue() * mix;
    params[3] += newMixParam;
    params[3] = std::fmin(std::fmax(params[3], 0), 1);
}
