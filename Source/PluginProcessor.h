/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"
#include "DSP/filterData.h"
#include "DSP/globalGain.h"
#include "DSP/lfoData.h"

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

    void fillArrays();
    void setLFOs(juce::AudioBuffer<float>& buffer);
    float getOutRMS(int channel);

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts {*this, nullptr, "Parameters", createParameterLayout()};

    juce::MidiKeyboardState keyState;
    Visualizer viz;

private:

    GlobalGain globalGain;
    juce::Synthesiser synth1;
    juce::Synthesiser synth2;
    FilterData filters;
    lfoData lfo1;
    lfoData lfo2;

    //Globas Var
    juce::AudioParameterFloat* gGain{ nullptr };
    juce::AudioParameterBool* bypassSynth1{ nullptr };
    juce::AudioParameterBool* bypassSynth2{ nullptr };
    juce::AudioParameterBool* bypassFilter{ nullptr };

    juce::AudioParameterInt* voices{ nullptr };

    //Osc1 Controls
    juce::AudioParameterFloat* attack1{nullptr};
    juce::AudioParameterFloat* decay1{nullptr};
    juce::AudioParameterFloat* sustain1{nullptr};
    juce::AudioParameterFloat* release1{nullptr};
    juce::AudioParameterFloat* oscGain1{nullptr};
    std::array<float, 5> osc1Params;

    //Osc1 Wave Type
    juce::AudioParameterBool* sine1{nullptr};
    juce::AudioParameterBool* saw1{nullptr};
    juce::AudioParameterBool* square1{nullptr};
    juce::AudioParameterBool* triangle1{nullptr};
    std::array<bool, 4> wavetype1;

    //Osc 2 Controls
    juce::AudioParameterFloat* attack2{nullptr};
    juce::AudioParameterFloat* decay2{nullptr};
    juce::AudioParameterFloat* sustain2{nullptr};
    juce::AudioParameterFloat* release2{nullptr};
    juce::AudioParameterFloat* oscGain2{nullptr};
    std::array<float, 5> osc2Params;

    //Osc 2 Wave Type
    juce::AudioParameterBool* sine2{nullptr};
    juce::AudioParameterBool* saw2{nullptr};
    juce::AudioParameterBool* square2{nullptr};
    juce::AudioParameterBool* triangle2{nullptr};
    std::array<bool, 4> wavetype2;

    //Fm Params
    juce::AudioParameterBool* fmOsc{nullptr};
    juce::AudioParameterFloat* fmDepth{nullptr};

    //Filter Select
    juce::AudioParameterChoice* filterType{ nullptr };

    //Ladder Params
    juce::AudioParameterChoice* ladderChoice{nullptr};
    juce::AudioParameterFloat* ladderFreq{nullptr};
    juce::AudioParameterFloat* ladderRes{nullptr};
    juce::AudioParameterFloat* ladderDrive{nullptr};
    std::array<float, 3> ladderParams;

    //Phaser Params
    juce::AudioParameterFloat* phaserRate{ nullptr };
    juce::AudioParameterFloat* phaserDepth{ nullptr };
    juce::AudioParameterFloat* phaserCenterFreq{ nullptr };
    juce::AudioParameterFloat* phaserFeedback{ nullptr };
    juce::AudioParameterFloat* phaserMix{ nullptr };
    std::array<float, 5> phaserParams;

    //Comb Params
    juce::AudioParameterFloat* combFreq{ nullptr };
    juce::AudioParameterFloat* combFeedback{ nullptr };
    juce::AudioParameterFloat* combGain{ nullptr };
    juce::AudioParameterFloat* combMix{ nullptr };
    std::array<float, 4> combParams;

    //RMS Out
    std::array<std::atomic<float>, 2> rmsOut{ -60, -60 };

    //LFO1 Wave Types
    juce::AudioParameterBool* lfo1sine{ nullptr };
    juce::AudioParameterBool* lfo1saw{ nullptr };
    juce::AudioParameterBool* lfo1square{ nullptr };
    juce::AudioParameterBool* lfo1triangle{ nullptr };

    //LFO1 Modulators
    juce::AudioParameterFloat* lfo1attack1{ nullptr };
    juce::AudioParameterFloat* lfo1decay1{ nullptr };
    juce::AudioParameterFloat* lfo1sustain1{ nullptr };
    juce::AudioParameterFloat* lfo1release1{ nullptr };
    juce::AudioParameterFloat* lfo1oscGain1{ nullptr };

    juce::AudioParameterFloat* lfo1attack2{ nullptr };
    juce::AudioParameterFloat* lfo1decay2{ nullptr };
    juce::AudioParameterFloat* lfo1sustain2{ nullptr };
    juce::AudioParameterFloat* lfo1release2{ nullptr };
    juce::AudioParameterFloat* lfo1oscGain2{ nullptr };

    juce::AudioParameterFloat* lfo1ladderFreq{ nullptr };
    juce::AudioParameterFloat* lfo1ladderRes{ nullptr };
    juce::AudioParameterFloat* lfo1ladderDrive{ nullptr };

    juce::AudioParameterFloat* lfo1phaserRate{ nullptr };
    juce::AudioParameterFloat* lfo1phaserDepth{ nullptr };
    juce::AudioParameterFloat* lfo1phaserCenterFreq{ nullptr };
    juce::AudioParameterFloat* lfo1phaserFeedback{ nullptr };
    juce::AudioParameterFloat* lfo1phaserMix{ nullptr };

    juce::AudioParameterFloat* lfo1combFreq{ nullptr };
    juce::AudioParameterFloat* lfo1combFeedback{ nullptr };
    juce::AudioParameterFloat* lfo1combGain{ nullptr };
    juce::AudioParameterFloat* lfo1combMix{ nullptr };

    juce::AudioParameterFloat* lfo1Rate{ nullptr };
    std::array<bool, 4> setLFO1Wave;
    float lfo1Output;

    //LFO1 Wave Types
    juce::AudioParameterBool* lfo2sine{ nullptr };
    juce::AudioParameterBool* lfo2saw{ nullptr };
    juce::AudioParameterBool* lfo2square{ nullptr };
    juce::AudioParameterBool* lfo2triangle{ nullptr };

    //LFO2 Modulators
    juce::AudioParameterFloat* lfo2attack1{ nullptr };
    juce::AudioParameterFloat* lfo2decay1{ nullptr };
    juce::AudioParameterFloat* lfo2sustain1{ nullptr };
    juce::AudioParameterFloat* lfo2release1{ nullptr };
    juce::AudioParameterFloat* lfo2oscGain1{ nullptr };

    juce::AudioParameterFloat* lfo2attack2{ nullptr };
    juce::AudioParameterFloat* lfo2decay2{ nullptr };
    juce::AudioParameterFloat* lfo2sustain2{ nullptr };
    juce::AudioParameterFloat* lfo2release2{ nullptr };
    juce::AudioParameterFloat* lfo2oscGain2{ nullptr };

    juce::AudioParameterFloat* lfo2ladderFreq{ nullptr };
    juce::AudioParameterFloat* lfo2ladderRes{ nullptr };
    juce::AudioParameterFloat* lfo2ladderDrive{ nullptr };

    juce::AudioParameterFloat* lfo2phaserRate{ nullptr };
    juce::AudioParameterFloat* lfo2phaserDepth{ nullptr };
    juce::AudioParameterFloat* lfo2phaserCenterFreq{ nullptr };
    juce::AudioParameterFloat* lfo2phaserFeedback{ nullptr };
    juce::AudioParameterFloat* lfo2phaserMix{ nullptr };

    juce::AudioParameterFloat* lfo2combFreq{ nullptr };
    juce::AudioParameterFloat* lfo2combFeedback{ nullptr };
    juce::AudioParameterFloat* lfo2combGain{ nullptr };
    juce::AudioParameterFloat* lfo2combMix{ nullptr };

    juce::AudioParameterFloat* lfo2Rate{ nullptr };
    std::array<bool, 4> setLFO2Wave;
    float lfo2Output;

    //RoadMap:
        //Bypass Buttons: DONE
            //Osc 1 DONE
            //Osc 2 DONE
            //Filter(s) DONE
        //Global Gain DONE
        //output meters DONE
        //LFO's DONE
            //Attach all the parms DONE
            //Create everything... twice DONE
            
    //Nice Haves (2.0?):
        //Dynamic Voice Adjustment
        //Pitch/Mod Wheel visuals
        //JUCE FFT Graphs
        //Preset Manager
        //Filters don't stay active when not displayed. 

    //Bugs/Design
        //Clicking when note finished playing DONE
        //Design Vertical and Horizontal Sliders DONE
        //Outlines/Seperators/backgrounds DONE
        //Fix Gloabl Gain Knob EH
        // Update Drop Down LNF DONE
        // Update Knobs so they don't change to wrong label DONE
        //Buttons clipping DONE
        //Adjust global area DONE


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessor)
};
