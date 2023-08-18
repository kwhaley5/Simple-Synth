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

private:

    Laf lnf;

    juce::ToggleButton sine     { "Sine" },
                       square   { "Square" },
                       saw      { "Saw" },
                       triangle { "Triangle" };

    //juce::Slider       attack1  /*{ "O1 Attack" }*/,
    //                   decay1   { "O1 Decay" },
    //                   sustain1 { "O1 Sustain" },
    //                   release1 { "O1 Release" },
    //                   gain1    { "O1 Gain" };

    //juce::Slider       attack2  { "O2 Attack" },
    //                   decay2   { "O2 Decay" },
    //                   sustain2 { "O2 Sustain" },
    //                   release2 { "O2 Release" },
    //                   gain2    { "O2 Gain" };

    //juce::Slider       cutoff    { "Ladder Cutoff" },
    //                   resonance { "Ladder Resonance" },
    //                   drive     { "Ladder Drive" };

    //juce::Slider       rate       { "Phaser Rate" },
    //                   depth      { "Phaser Depth" },
    //                   centerFreq { "Phaser Center Freq" },
    //                   pFeedback  { "Phaser Feedback" },
    //                   pMix       { "Phaser Mix" };

    //juce::Slider       freq       { "Comb Freq" },
    //                   cFeedback  { "Comb Feedback" },
    //                   cGain      { "Comb Gain" },
    //                   cMix       { "Comb Mix" };

    juce::Slider       attack1  /*{ "O1 Attack" }*/,
                       decay1   ,
                       sustain1 ,
                       release1 ,
                       gain1   ;

    juce::Slider       attack2  ,
                       decay2  ,
                       sustain2 ,
                       release2 ,
                       gain2   ;

    juce::Slider       cutoff    ,
                       resonance ,
                       drive     ;

    juce::Slider       rate       ,
                       depth      ,
                       centerFreq ,
                       pFeedback  ,
                       pMix       ;

    juce::Slider       freq      ,
                       cFeedback  ,
                       cGain      ,
                       cMix       ;

    juce::Slider lfoRate;

    juce::GroupComponent Osc1{ "Osc 1", "Osc 1" };
    juce::GroupComponent Osc2{ "Osc 2", "Osc 2" };
    juce::GroupComponent Filter{"Filter", "Filter"};
    juce::TooltipWindow name{ this, 100 };

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> attack1AT;
};