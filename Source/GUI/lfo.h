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
    void setRight(juce::Rectangle<int>& bounds);

    void updateToggleState(juce::Button* button);
    void getComboValue(int combo);

private:

    Laf lnf;

    juce::ToggleButton sine     { "Sine" },
                       square   { "Square" },
                       saw      { "Saw" },
                       triangle { "Tri" };
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

    juce::Slider       cutoff    { "Ladder Cutoff" },
                       resonance { "Ladder Resonance" },
                       drive     { "Ladder Drive" };

    juce::Slider       rate       { "Phaser Rate" },
                       depth      { "Phaser Depth" },
                       centerFreq { "Phaser Center Freq" },
                       pFeedback  { "Phaser Feedback" },
                       pMix       { "Phaser Mix" };

    juce::Slider       freq       { "comb freq" },
                       cFeedback  { "comb feedback" },
                       cGain      { "comb gain" },
                       cMix       { "comb mix" };
    juce::AudioProcessorValueTreeState::SliderAttachment attack1AT, decay1AT,    sustain1AT,   release1AT,  gain1AT, 
                                                         attack2AT, decay2AT,    sustain2AT,   release2AT,  gain2AT,
                                                         cutoffAT,  resonanceAT, driveAT,
                                                         rateAT,    depthAT,     centerFreqAT, pFeedbackAT, pMixAT,
                                                         freqAT,    cFeedbackAT, cGainAT,      cMixAT;

    juce::ToggleButton sine2     { "Sine" },
                       square2   { "Square" },
                       saw2      { "Saw" },
                       triangle2 { "Tri" };
    juce::AudioProcessorValueTreeState::ButtonAttachment sine2AT, square2AT, saw2AT, triangle2AT;

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

    juce::Slider       cutoff2    { "Ladder Cutoff" },
                       resonance2 { "Ladder Resonance" },
                       drive2     { "Ladder Drive" };

    juce::Slider       rate2       { "Phaser Rate" },
                       depth2      { "Phaser Depth" },
                       centerFreq2 { "Phaser Center Freq" },
                       pFeedback2  { "Phaser Feedback" },
                       pMix2       { "Phaser Mix" };

    juce::Slider       freq2       { "Comb Freq" },
                       cFeedback2  { "Comb Feedback" },
                       cGain2      { "Comb Gain" },
                       cMix2       { "Comb Mix" };
    juce::AudioProcessorValueTreeState::SliderAttachment attack12AT, decay12AT,    sustain12AT, release12AT, gain12AT,
                                                         attack22AT, decay22AT,    sustain22AT, release22AT, gain22AT,
                                                         cutoff2AT,  resonance2AT, drive2AT,
                                                         rate2AT,    depth2AT,     centerFreq2AT, pFeedback2AT, pMix2AT,
                                                         freq2AT,    cFeedback2AT, cGain2AT,      cMix2AT;   

    juce::Slider lfoRate1 {"Rate"}, 
                 lfoRate2{ "Rate" };
    juce::AudioProcessorValueTreeState::SliderAttachment lfoRate1AT, lfoRate2AT;

    juce::GroupComponent Osc1{ "Osc 1", "Osc 1" };
    juce::GroupComponent Osc2{ "Osc 2", "Osc 2" };
    juce::GroupComponent Filter{"Filter", "Filter"};

    juce::GroupComponent Osc12{ "Osc 1", "Osc 1" };
    juce::GroupComponent Osc22{ "Osc 2", "Osc 2" };
    juce::GroupComponent Filter2{ "Filter", "Filter" };

    juce::Slider comboChange;
};