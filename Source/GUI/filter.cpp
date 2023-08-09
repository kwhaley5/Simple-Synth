/*
  ==============================================================================

    filter.cpp
    Created: 8 Aug 2023 5:43:01pm
    Author:  kylew

  ==============================================================================
*/

#include "filter.h"

FilterComp::FilterComp(juce::AudioProcessorValueTreeState& apvts) :
    ladderFreqAT(apvts, "ladderFreq", ladderFreq),
    ladderResAT(apvts, "ladderRes", ladderRes),
    ladderDriveAT(apvts, "ladderDrive", ladderDrive)
    //ladderModeAT(apvts, "ladderChoice", ladderMode)
{
    setLookAndFeel(&lnf);

    juce::StringArray choices{ "LP12", "HP12", "BP12", "LP24", "HP24", "BP24" };
    ladderMode.addItemList(choices, 1);
    addAndMakeVisible(ladderMode);

    ladderModeAT = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "ladderChoice", ladderMode);

    setRotarySlider(ladderFreq);
    setRotarySlider(ladderRes);
    setRotarySlider(ladderDrive);
}

FilterComp::~FilterComp()
{
    setLookAndFeel(nullptr);
}

void FilterComp::paint(juce::Graphics& g)

{
}

void FilterComp::resized()
{
    auto bounds = getLocalBounds();
    auto dialArea = bounds.removeFromBottom(bounds.getHeight() * .4);
    auto comboArea = bounds.removeFromBottom(bounds.getHeight() * .167);
    ladderMode.setBounds(comboArea);

    auto freqArea = dialArea.removeFromLeft(dialArea.getWidth() * .33);
    ladderFreq.setBounds(freqArea);
    auto resArea = dialArea.removeFromLeft(dialArea.getWidth() * .5);
    ladderRes.setBounds(resArea);
    auto driveArea = dialArea.removeFromLeft(dialArea.getWidth());
    ladderDrive.setBounds(driveArea);
}

void FilterComp::setRotarySlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 1, 1);
    slider.setName(slider.getComponentID());
    addAndMakeVisible(slider);
}
