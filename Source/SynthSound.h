/*
  ==============================================================================

    SynthSound.h
    Created: 2 Aug 2023 10:44:44am
    Author:  kylew

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct SynthSound : public juce::SynthesiserSound
{
    bool appliesToNote(int midiNoteNumber) override { return true; };
    bool appliesToChannel(int midiChannel) override { return true; };
};