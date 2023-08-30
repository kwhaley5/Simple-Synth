/*
  ==============================================================================

    filterData.cpp
    Created: 8 Aug 2023 4:49:11pm
    Author:  kylew

  ==============================================================================
*/

#include "filterData.h"

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    ladderFilter.reset();
    phaserFilter.reset();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    ladderFilter.prepare(spec);
    phaserFilter.prepare(spec);

    for (auto& c : combFilter)
    {
        c.reset();
        c.prepare(spec);
        c.setMaximumDelayInSamples(sampleRate);
    }
    for (auto& s : smoothedDelay)
    {
        s.reset(sampleRate, .05);
        s.setCurrentAndTargetValue(.5);
    }
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    auto block = juce::dsp::AudioBlock<float>(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    ladderFilter.process(context);
    phaserFilter.process(context);
}

void FilterData::updateLadderParams(int mode, float cuttoffFreq, float resonance, float drive)
{
    switch (mode)
    {
    case 0:
        ladderFilter.setMode(juce::dsp::LadderFilterMode::LPF12);
        break;
    case 1:
        ladderFilter.setMode(juce::dsp::LadderFilterMode::HPF12);
        break;
    case 2:
        ladderFilter.setMode(juce::dsp::LadderFilterMode::BPF12);
        break;
    case 3:
        ladderFilter.setMode(juce::dsp::LadderFilterMode::LPF24);
        break;
    case 4:
        ladderFilter.setMode(juce::dsp::LadderFilterMode::HPF24);
        break;
    case 5:
        ladderFilter.setMode(juce::dsp::LadderFilterMode::BPF24);
        break;
    }

    ladderFilter.setCutoffFrequencyHz(cuttoffFreq);
    ladderFilter.setResonance(resonance);
    ladderFilter.setDrive(drive);

}

void FilterData::updatePhaserParams(float rate, float depth, float centerFreq, float feedback, float mix)
{
    phaserFilter.setRate(rate);
    phaserFilter.setDepth(depth);
    phaserFilter.setCentreFrequency(centerFreq);
    phaserFilter.setFeedback(feedback);
    phaserFilter.setMix(mix);
}

void FilterData::processComb(int channel, juce::AudioBuffer<float>& buffer, float freq, float feedback, float gain, float mix, double sampleRate)
{
    //comb filtering is selayed signal. My implmentation with delayline
    smoothedDelay[channel].setTargetValue(freq/1000);
    auto block = juce::dsp::AudioBlock<float>(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    auto& inputBlock = context.getInputBlock();
    auto& ouputBlock = context.getOutputBlock();
    auto numSamples = ouputBlock.getNumSamples();

    auto* input = inputBlock.getChannelPointer(channel);
    auto* output = ouputBlock.getChannelPointer(channel);

    for (int i = 0; i < numSamples; i++)
    {
        auto nextDelayTime = smoothedDelay[channel].getNextValue() * sampleRate;
        auto delayedSample = combFilter[channel].popSample(channel, nextDelayTime);
        auto inDelay = std::tanh(input[i] + feedback * delayedSample);
        combFilter[channel].pushSample(channel, inDelay);
        output[i] = (input[i] * (1 - mix)) + (delayedSample * mix * gain);
    }

}

void FilterData::reset(int filterChoice)
{
    if(filterChoice == 0)
        phaserFilter.reset();
    else if(filterChoice == 1)
        ladderFilter.reset();
    
}
