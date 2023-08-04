/*
  ==============================================================================

    adsr.h
    Created: 2 Aug 2023 2:32:05pm
    Author:  kylew

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "KiTiKLNF.h"

struct OscComp : public juce::Component
{
    OscComp(juce::AudioProcessorValueTreeState& apvts);
    ~OscComp();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setSlider(juce::Slider&);
    void setRotarySlider(juce::Slider&);
    void updateToggleState(juce::Button&);

private:

    Laf lnf;

    juce::ToggleButton sine   {"Sine"}, 
                       square {"Square"}, 
                       saw    { "Saw" };
    juce::Slider attack, decay, sustain, release;
    juce::Slider gain;

    juce::AudioProcessorValueTreeState::SliderAttachment attackAT, decayAT, sustainAT, releaseAT;
    juce::AudioProcessorValueTreeState::SliderAttachment gainAT;
    juce::AudioProcessorValueTreeState::ButtonAttachment sineAT, squareAT, sawAT;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscComp);
};