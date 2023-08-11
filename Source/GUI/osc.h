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
    void setHorzSlider(juce::Slider&);
    void setRotarySlider(juce::Slider&);
    void updateToggleState(juce::Button*);

private:

    Laf lnf;

    juce::ToggleButton sine1     {"Sine"},
                       square1   { "Square" },
                       saw1      { "Saw" },
                       triangle1 { "Triangle" };
    juce::Slider       attack1   { "Attack" },
                       decay1    { "Decay" },
                       sustain1  { "Sustain" },
                       release1  { "Release" },
                       gain1     { "Gain" };

    juce::AudioProcessorValueTreeState::SliderAttachment attackAT1, decayAT1, sustainAT1, releaseAT1;
    juce::AudioProcessorValueTreeState::SliderAttachment gainAT1;
    juce::AudioProcessorValueTreeState::ButtonAttachment sineAT1, squareAT1, sawAT1, triangleAT1;

    juce::ToggleButton sine2     {"Sine"},
                       square2   { "Square" },
                       saw2      { "Saw" },
                       triangle2 { "Triangle" };
    juce::Slider       attack2   { "Attack" },
                       decay2    { "Decay" },
                       sustain2  { "Sustain" },
                       release2  { "Release" },
                       gain2     { "Gain" };

    juce::AudioProcessorValueTreeState::SliderAttachment attackAT2, decayAT2, sustainAT2, releaseAT2;
    juce::AudioProcessorValueTreeState::SliderAttachment gainAT2;
    juce::AudioProcessorValueTreeState::ButtonAttachment sineAT2, squareAT2, sawAT2, triangleAT2;

    juce::ToggleButton fmOsc;
    juce::Slider fmDepth{ "Depth" };
    juce::AudioProcessorValueTreeState::ButtonAttachment fmOscAT;
    juce::AudioProcessorValueTreeState::SliderAttachment fmDepthAT;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscComp);
};