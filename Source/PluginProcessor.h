/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
/**
*/

class SimpleSynthAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    SimpleSynthAudioProcessor();
    ~SimpleSynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts {*this, nullptr, "Parameters", createParameterLayout()};

private:

    juce::Synthesiser synth1;
    juce::Synthesiser synth2;

    juce::AudioParameterFloat* attack1{nullptr};
    juce::AudioParameterFloat* decay1{nullptr};
    juce::AudioParameterFloat* sustain1{nullptr};
    juce::AudioParameterFloat* release1{nullptr};
    juce::AudioParameterFloat* oscGain1{nullptr};

    juce::AudioParameterBool* sine1{nullptr};
    juce::AudioParameterBool* saw1{nullptr};
    juce::AudioParameterBool* square1{nullptr};
    juce::AudioParameterBool* triangle1{nullptr};

    std::array<bool, 4> wavetype1;

    juce::AudioParameterFloat* attack2{nullptr};
    juce::AudioParameterFloat* decay2{nullptr};
    juce::AudioParameterFloat* sustain2{nullptr};
    juce::AudioParameterFloat* release2{nullptr};
    juce::AudioParameterFloat* oscGain2{nullptr};

    juce::AudioParameterBool* sine2{nullptr};
    juce::AudioParameterBool* saw2{nullptr};
    juce::AudioParameterBool* square2{nullptr};
    juce::AudioParameterBool* triangle2{nullptr};

    std::array<bool, 4> wavetype2;

    juce::AudioParameterBool* fmOsc{nullptr};
    juce::AudioParameterFloat* fmDepth{nullptr};

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessor)
};
