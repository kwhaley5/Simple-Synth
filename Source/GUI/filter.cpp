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
    ladderDriveAT(apvts, "ladderDrive", ladderDrive),
    phaserRateAT(apvts, "phaserRate", phaserRate),
    phaserDepthAT(apvts, "phaserDepth", phaserDepth),
    phaserCenterFreqAT(apvts, "phaserCenterFreq", phaserCenterFreq),
    phaserFeedbackAT(apvts, "phaserFeedback", phaserFeedback),
    phaserMixAT(apvts, "phaserMix", phaserMix), 
    combFreqAT(apvts, "combFreq", combFreq),
    combFeeedbackAT(apvts, "combFeedback", combFeedback),
    combGainAT(apvts, "combGain", combGain),
    combMixAT(apvts, "combMix", combMix)
{
    setLookAndFeel(&lnf);

    juce::StringArray choicesFilter{ "Ladder", "Phaser", "Comb"};
    filterType.addItemList(choicesFilter, 1);
    addAndMakeVisible(filterType);
    filterTypeAT = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "filterType", filterType);

    juce::StringArray choicesLadder{ "LP12", "HP12", "BP12", "LP24", "HP24", "BP24" };
    ladderMode.addItemList(choicesLadder, 1);
    addAndMakeVisible(ladderMode);
    ladderModeAT = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "ladderChoice", ladderMode);

    setRotarySlider(ladderFreq);
    setRotarySlider(ladderRes);
    setRotarySlider(ladderDrive);

    setRotarySlider(phaserRate);
    setRotarySlider(phaserDepth);
    setRotarySlider(phaserCenterFreq);
    setRotarySlider(phaserFeedback);
    setRotarySlider(phaserMix);

    setRotarySlider(combFreq);
    setRotarySlider(combFeedback);
    setRotarySlider(combGain);
    setRotarySlider(combMix);

    phaserRate.setVisible(false);
    phaserDepth.setVisible(false);
    phaserCenterFreq.setVisible(false);
    phaserFeedback.setVisible(false);
    phaserMix.setVisible(false);

    combFreq.setVisible(false);
    combFeedback.setVisible(false);
    combGain.setVisible(false);
    combMix.setVisible(false);

    filterType.onChange = [this]()
    {
        if (filterType.getSelectedId() == 1)
        {
            ladderFreq.setVisible(true);
            ladderRes.setVisible(true);
            ladderDrive.setVisible(true);
            ladderMode.setVisible(true);

            phaserRate.setVisible(false);
            phaserDepth.setVisible(false);
            phaserCenterFreq.setVisible(false);
            phaserFeedback.setVisible(false);
            phaserMix.setVisible(false);

            combFreq.setVisible(false);
            combFeedback.setVisible(false);
            combGain.setVisible(false);
            combMix.setVisible(false);
            resized();
         
        }
        else if (filterType.getSelectedId() == 2)
        {
            ladderFreq.setVisible(false);
            ladderRes.setVisible(false);
            ladderDrive.setVisible(false);
            ladderMode.setVisible(false);

            phaserRate.setVisible(true);
            phaserDepth.setVisible(true);
            phaserCenterFreq.setVisible(true);
            phaserFeedback.setVisible(true);
            phaserMix.setVisible(true);

            combFreq.setVisible(false);
            combFeedback.setVisible(false);
            combGain.setVisible(false);
            combMix.setVisible(false);
            resized();
        }
        else
        {
            ladderFreq.setVisible(false);
            ladderRes.setVisible(false);
            ladderDrive.setVisible(false);
            ladderMode.setVisible(false);

            phaserRate.setVisible(false);
            phaserDepth.setVisible(false);
            phaserCenterFreq.setVisible(false);
            phaserFeedback.setVisible(false);
            phaserMix.setVisible(false);

            combFreq.setVisible(true);
            combFeedback.setVisible(true);
            combGain.setVisible(true);
            combMix.setVisible(true);
            resized();
        }
    };
}

FilterComp::~FilterComp()
{
    setLookAndFeel(nullptr);
}

void FilterComp::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    auto dialArea = bounds.removeFromBottom(bounds.getHeight() * .4);
    auto comboArea = bounds.removeFromBottom(bounds.getHeight() * .167);

    g.setColour(juce::Colours::black);
    g.fillRect(bounds.reduced(10));
    g.setColour(juce::Colours::white);
    g.drawFittedText("Filter Graph Here", bounds, juce::Justification::centred, 1);
}

void FilterComp::resized()
{
    auto bounds = getLocalBounds();
    auto dialArea = bounds.removeFromBottom(bounds.getHeight() * .4);
    auto dialAreaPhaser = dialArea;
    auto dialAreaComb = dialArea;
    auto comboArea = bounds.removeFromBottom(bounds.getHeight() * .167);
    comboArea = comboArea.removeFromLeft(comboArea.getWidth() - 10);
    comboArea = comboArea.removeFromRight(comboArea.getWidth() - 10);

    juce::FlexBox flexbox;
    flexbox.flexDirection = juce::FlexBox::Direction::row;
    flexbox.flexWrap = juce::FlexBox::Wrap::noWrap;

    flexbox.items.add(juce::FlexItem(filterType).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(ladderMode).withFlex(1.f));

    if (!ladderMode.isVisible())
        flexbox.items.removeLast(1);
    
    flexbox.performLayout(comboArea);

    auto freqArea = dialArea.removeFromLeft(dialArea.getWidth() * .33);
    ladderFreq.setBounds(freqArea);
    auto resArea = dialArea.removeFromLeft(dialArea.getWidth() * .5);
    ladderRes.setBounds(resArea);
    auto driveArea = dialArea.removeFromLeft(dialArea.getWidth());
    ladderDrive.setBounds(driveArea);

    auto rateArea = dialAreaPhaser.removeFromLeft(dialAreaPhaser.getWidth() * .2);
    phaserRate.setBounds(rateArea);
    auto depthArea = dialAreaPhaser.removeFromLeft(dialAreaPhaser.getWidth() * .25);
    phaserDepth.setBounds(depthArea);
    auto centerFreqArea = dialAreaPhaser.removeFromLeft(dialAreaPhaser.getWidth() * .33);
    phaserCenterFreq.setBounds(centerFreqArea);
    auto feedbackArea = dialAreaPhaser.removeFromLeft(dialAreaPhaser.getWidth() * .5);
    phaserFeedback.setBounds(feedbackArea);
    auto mixArea = dialAreaPhaser.removeFromLeft(dialAreaPhaser.getWidth());
    phaserMix.setBounds(mixArea);

    auto freqAreaComb = dialAreaComb.removeFromLeft(dialAreaComb.getWidth() * .25);
    combFreq.setBounds(freqAreaComb);
    auto feedbackAreaComb = dialAreaComb.removeFromLeft(dialAreaComb.getWidth() * .33);
    combFeedback.setBounds(feedbackAreaComb);
    auto gainAreaComb = dialAreaComb.removeFromLeft(dialAreaComb.getWidth() * .5);
    combGain.setBounds(gainAreaComb);
    auto mixAreaComb = dialAreaComb.removeFromLeft(dialAreaComb.getWidth());
    combMix.setBounds(mixAreaComb);
}

void FilterComp::setRotarySlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 1, 1);
    addAndMakeVisible(slider);
}
