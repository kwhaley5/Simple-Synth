/*
  ==============================================================================

    lfo.h
    Created: 17 Aug 2023 4:14:19pm
    Author:  kylew

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "KiTiKLNF.h"
#include "osc.h"

struct LFOComp : public juce::Component
{
    LFOComp(juce::AudioProcessorValueTreeState& apvts);
    ~LFOComp();

    void paint(juce::Graphics& g) override;
    void resized() override;
    void setSlider(juce::Slider&);
    void setRotarySlider(juce::Slider&);
    void setGroupComp(juce::GroupComponent&);

    void setLeft(juce::Rectangle<int>& bounds);

private:

    Laf lnf;

    juce::ToggleButton sine     { "Sine" },
                       square   { "Square" },
                       saw      { "Saw" },
                       triangle { "Triangle" };
    juce::AudioProcessorValueTreeState::ButtonAttachment sineAT, squareAT, sawAT, triangleAT;

    juce::Slider       attack1  { "O1 Attack" },
                       decay1   { "O1 Decay" },
                       sustain1 { "O1 Sustain" },
                       release1 { "O1 Release" },
                       gain1    { "O1 Gain" };

    juce::Slider       attack2  { "O2 Attack" },
                       decay2   { "O2 Decay" },
                       sustain2 { "O2 Sustain" },
                       release2 { "O2 Release" },
                       gain2    { "O2 Gain" };

    //juce::Slider       cutoff    { "Ladder Cutoff" },
    //                   resonance { "Ladder Resonance" },
    //                   drive     { "Ladder Drive" };

    juce::Slider       rate       { "Phaser Rate" },
                       depth      { "Phaser Depth" },
                       centerFreq { "Phaser Center Freq" },
                       pFeedback  { "Phaser Feedback" },
                       pMix       { "Phaser Mix" };

    //juce::Slider       freq       { "Comb Freq" },
    //                   cFeedback  { "Comb Feedback" },
    //                   cGain      { "Comb Gain" },
    //                   cMix       { "Comb Mix" };
    juce::AudioProcessorValueTreeState::SliderAttachment attack1AT, decay1AT, sustain1AT, release1AT, gain1AT, attack2AT, decay2AT, sustain2AT, release2AT, gain2AT, rateAT, depthAT, centerFreqAT, pFeedbackAT, pMixAT;

    juce::ToggleButton sine2     { "Sine" },
                       square2   { "Square" },
                       saw2      { "Saw" },
                       triangle2 { "Triangle" };

    juce::Slider       attack12  { "O1 Attack" },
                       decay12   { "O1 Decay" },
                       sustain12 { "O1 Sustain" },
                       release12 { "O1 Release" },
                       gain12    { "O1 Gain" };

    juce::Slider       attack22  { "O2 Attack" },
                       decay22   { "O2 Decay" },
                       sustain22 { "O2 Sustain" },
                       release22 { "O2 Release" },
                       gain22    { "O2 Gain" };

    //juce::Slider       cutoff2    { "Ladder Cutoff" },
    //                   resonance2 { "Ladder Resonance" },
    //                   drive2     { "Ladder Drive" };

    juce::Slider       rate2       { "Phaser Rate" },
                       depth2      { "Phaser Depth" },
                       centerFreq2 { "Phaser Center Freq" },
                       pFeedback2  { "Phaser Feedback" },
                       pMix2       { "Phaser Mix" };

    //juce::Slider       freq2       { "Comb Freq" },
    //                   cFeedback2  { "Comb Feedback" },
    //                   cGain2      { "Comb Gain" },
    //                   cMix2       { "Comb Mix" };

    juce::Slider lfoRate1, lfoRate2;
    juce::AudioProcessorValueTreeState::SliderAttachment lfoRate1AT;

    juce::GroupComponent Osc1{ "Osc 1", "Osc 1" };
    juce::GroupComponent Osc2{ "Osc 2", "Osc 2" };
    juce::GroupComponent Filter{"Filter", "Filter"};
    juce::TooltipWindow name{ this, 100 };
};