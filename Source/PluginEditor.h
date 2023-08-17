/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/KiTiKLNF.h"
#include "GUI/osc.h"
#include "GUI/filter.h"
#include "GUI/GlobalControls.h"

//==============================================================================
/**
*/
class SimpleSynthAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Timer
{
public:
    SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor&);
    ~SimpleSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void setKeyboard();

private:
    SimpleSynthAudioProcessor& audioProcessor;

    Laf lnf;

    OscComp oscComp{audioProcessor.apvts};
    FilterComp filterComp{ audioProcessor.apvts };
    GlobalControls globalControls{ audioProcessor.apvts };

    
    juce::MidiKeyboardComponent keyboard{ audioProcessor.keyState, juce::KeyboardComponentBase::horizontalKeyboard };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessorEditor)
};
