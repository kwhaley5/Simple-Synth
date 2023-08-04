/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/osc.h"

//==============================================================================
/**
*/
class SimpleSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor&);
    ~SimpleSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SimpleSynthAudioProcessor& audioProcessor;

    OscComp oscComp1{audioProcessor.apvts};
    OscComp oscComp2{ audioProcessor.apvts };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessorEditor)
};
