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
    void updateToggleState(juce::Button*);

private:

    Laf lnf;

    juce::ToggleButton sine1     {"Sine"},
                       square1   { "Square" },
                       saw1      { "Saw" },
                       triangle1 { "Triangle" };
    juce::Slider attack1, decay1, sustain1, release1;
    juce::Slider gain1;

    juce::AudioProcessorValueTreeState::SliderAttachment attackAT1, decayAT1, sustainAT1, releaseAT1;
    juce::AudioProcessorValueTreeState::SliderAttachment gainAT1;
    juce::AudioProcessorValueTreeState::ButtonAttachment sineAT1, squareAT1, sawAT1, triangleAT1;

    juce::ToggleButton sine2     {"Sine"},
                       square2   { "Square" },
                       saw2      { "Saw" },
                       triangle2 { "Triangle" };
    juce::Slider attack2, decay2, sustain2, release2;
    juce::Slider gain2;

    juce::AudioProcessorValueTreeState::SliderAttachment attackAT2, decayAT2, sustainAT2, releaseAT2;
    juce::AudioProcessorValueTreeState::SliderAttachment gainAT2;
    juce::AudioProcessorValueTreeState::ButtonAttachment sineAT2, squareAT2, sawAT2, triangleAT2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscComp);
};