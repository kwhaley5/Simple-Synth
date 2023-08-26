/*
  ==============================================================================

    SynthVoice.cpp
    Created: 2 Aug 2023 10:44:33am
    Author:  kylew

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr; //Make sure we have an actual synth sound
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setWaveFreq(midiNoteNumber, 0, false, 0); //Need to change back
    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
    if (!isVoiceActive())
        return;

    //Gets rid of clipping when switching between notes
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    auto block = juce::dsp::AudioBlock<float>(synthBuffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    osc.processNextBlock(context);

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    for (auto ch = 0; ch < outputBuffer.getNumChannels(); ++ch)
    {
        outputBuffer.addFrom(ch, startSample, synthBuffer, ch, 0, numSamples);

        if (!adsr.isActive())
        {
            clearCurrentNote();
        }
            
    }
}

void SynthVoice::update(float attack, float decay, float sustain, float release, float gain)
{
    adsr.setADSR(attack, decay, sustain, release);
    osc.setGain(gain);
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;
    spec.sampleRate = sampleRate;

    osc.prepareToPlay(spec);
}
