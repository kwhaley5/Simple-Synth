/*
  ==============================================================================

    lfo.cpp
    Created: 17 Aug 2023 4:14:19pm
    Author:  kylew

  ==============================================================================
*/

#include "lfo.h"

LFOComp::LFOComp(juce::AudioProcessorValueTreeState& apvts)
{
    setLookAndFeel(&lnf);

    addAndMakeVisible(sine);
    addAndMakeVisible(saw);
    addAndMakeVisible(square);
    addAndMakeVisible(triangle);

    setRotarySlider(attack1);
    setRotarySlider(decay1);
    setRotarySlider(sustain1);
    setRotarySlider(release1);

    setRotarySlider(attack2);
    setRotarySlider(decay2);
    setRotarySlider(sustain2);
    setRotarySlider(release2);

    setRotarySlider(gain1);
    setRotarySlider(gain2);

    setRotarySlider(cutoff);
    setRotarySlider(resonance);
    setRotarySlider(drive);

    setRotarySlider(rate);
    setRotarySlider(depth);
    setRotarySlider(centerFreq);
    setRotarySlider(pFeedback);
    setRotarySlider(pMix);

    setRotarySlider(freq);
    setRotarySlider(cFeedback);
    setRotarySlider(cGain);
    setRotarySlider(cMix);
}

LFOComp::~LFOComp()
{
    setLookAndFeel(nullptr);
}

void LFOComp::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(10);

    auto buttonArea = bounds.removeFromTop(bounds.getHeight() * .25);
    auto adsr1Area = bounds.removeFromTop(bounds.getHeight() * .33);
    auto adsr2Area = bounds.removeFromTop(bounds.getHeight() * .5);
    auto filterArea = bounds;

}

void LFOComp::resized()
{
    auto bounds = getLocalBounds().reduced(10);

    auto buttonArea = bounds.removeFromTop(bounds.getHeight() * .25);
    auto adsr1Area = bounds.removeFromTop(bounds.getHeight() * .33);
    auto adsr2Area = bounds.removeFromTop(bounds.getHeight() * .5);
    auto filterArea = bounds;

    juce::FlexBox flexbox;
    flexbox.flexDirection = juce::FlexBox::Direction::row;
    flexbox.flexWrap = juce::FlexBox::Wrap::noWrap;

    flexbox.items.add(juce::FlexItem(sine).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(saw).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(square).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(triangle).withFlex(1.f));
    flexbox.performLayout(buttonArea);
    
    flexbox.items.clear();
    flexbox.items.add(juce::FlexItem(attack1).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(decay1).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(sustain1).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(release1).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(gain1).withFlex(1.f));
    flexbox.performLayout(adsr1Area);

    flexbox.items.clear();
    flexbox.items.add(juce::FlexItem(attack2).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(decay2).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(sustain2).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(release2).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(gain2).withFlex(1.f));
    flexbox.performLayout(adsr2Area);

    flexbox.items.clear();
    flexbox.items.add(juce::FlexItem(rate).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(depth).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(centerFreq).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(pFeedback).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(pMix).withFlex(1.f));
    flexbox.performLayout(filterArea);


}

void LFOComp::setRotarySlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 1, 1);
    addAndMakeVisible(slider);
}
