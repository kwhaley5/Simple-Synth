/*
  ==============================================================================

    adsr.cpp
    Created: 2 Aug 2023 2:32:05pm
    Author:  kylew

  ==============================================================================
*/

#include "osc.h"

OscComp::OscComp(juce::AudioProcessorValueTreeState& apvts) :
    attackAT(apvts, "attack1", attack),
    decayAT(apvts, "decay1", decay),
    sustainAT(apvts, "sustain1", sustain),
    releaseAT(apvts, "release1", release),
    gainAT(apvts, "oscGain1", gain),
    sineAT(apvts, "sine1", sine),
    sawAT(apvts, "saw1", saw),
    squareAT(apvts, "square1", square)
{
    setLookAndFeel(&lnf);

    setSlider(attack);
    setSlider(decay);
    setSlider(sustain);
    setSlider(release);
    setRotarySlider(gain);

    addAndMakeVisible(sine);
    addAndMakeVisible(saw);
    addAndMakeVisible(square);

    sine.onClick = [this] {updateToggleState(sine); };
    saw.onClick = [this] {updateToggleState(saw); };
    square.onClick = [this] {updateToggleState(square); };

    sine.setRadioGroupId(1);
    saw.setRadioGroupId(1);
    square.setRadioGroupId(1);
}

OscComp::~OscComp()
{
    setLookAndFeel(nullptr);
}

void OscComp::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);

    auto adsrBounds = bounds.removeFromBottom(bounds.getHeight() * .4);
    auto waveTypeBounds = bounds.removeFromBottom(bounds.getHeight() * .166);
    auto gainBounds = bounds.removeFromBottom(bounds.getHeight() * .2);

    g.fillRect(bounds.reduced(10));
    g.setColour(juce::Colours::white);
    g.drawFittedText("Osc picture here", bounds, juce::Justification::centred, 1);

}

void OscComp::resized()
{
    auto bounds = getLocalBounds().reduced(5);

    auto adsrBounds = bounds.removeFromBottom(bounds.getHeight() * .4);
    auto waveTypeBounds = bounds.removeFromBottom(bounds.getHeight() * .166);
    auto gainBounds = bounds.removeFromBottom(bounds.getHeight() * .2);
    gain.setBounds(gainBounds);

    auto sineBounds = waveTypeBounds.removeFromLeft(waveTypeBounds.getWidth() * .33);
    sine.setBounds(sineBounds);
    auto sawBounds = waveTypeBounds.removeFromLeft(waveTypeBounds.getWidth() * .5);
    saw.setBounds(sawBounds);
    auto squareBounds = waveTypeBounds.removeFromLeft(waveTypeBounds.getWidth());
    square.setBounds(squareBounds);

    auto attackBounds = adsrBounds.removeFromLeft(adsrBounds.getWidth() * .25);
    attack.setBounds(attackBounds);
    auto decayBounds = adsrBounds.removeFromLeft(adsrBounds.getWidth() * .33);
    decay.setBounds(decayBounds);
    auto sustainBounds = adsrBounds.removeFromLeft(adsrBounds.getWidth() * .5);
    sustain.setBounds(sustainBounds);
    auto releaseBounds = adsrBounds.removeFromLeft(adsrBounds.getWidth());
    release.setBounds(releaseBounds);

}

void OscComp::setSlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 1, 1);
    slider.setName(slider.getComponentID());
    addAndMakeVisible(slider);
}

void OscComp::setRotarySlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 1, 1);
    slider.setName(slider.getComponentID());
    addAndMakeVisible(slider);
}

void OscComp::updateToggleState(juce::Button& button)
{
    auto state = button.getToggleState();
}
