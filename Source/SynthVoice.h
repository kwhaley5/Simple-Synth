/*
  ==============================================================================

    SynthVoice.h
    Created: 2 Aug 2023 10:44:33am
    Author:  kylew

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "DSP/oscData.h"
#include <math.h>

struct SynthVoice : public juce::SynthesiserVoice
{
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void setADSR(float attack, float decay, float sustain, float release);
    void setGain(float gain);
    oscData& getOscillator() { return osc; }

private:
    oscData osc;
    //juce::dsp::Oscillator<float> osc{ [](float x) {return std::sin(x); } };
    juce::AudioBuffer<float> synthBuffer;
    juce::dsp::Gain<float> oscGain;

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;

    // x / juce::MathConstants<float>::pi; //Saw Wave
    // x <0.0f ? -1.f : 1.f; //Square Wave
    // std::asin(std::cos(x))/juce::MathConstants<float>::halfPi //Triangle
};