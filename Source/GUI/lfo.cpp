/*
  ==============================================================================

    lfo.cpp
    Created: 17 Aug 2023 4:14:19pm
    Author:  kylew

  ==============================================================================
*/

#include "lfo.h"

LFOComp::LFOComp(juce::AudioProcessorValueTreeState& apvts) :
    //LFO type and RAte
    sineAT(apvts, "lfo1sine", sine), sawAT(apvts, "lfo1saw", saw), squareAT(apvts, "lfo1square", square), triangleAT(apvts, "lfo1triangle", triangle), lfoRate1AT(apvts, "lfo1Rate", lfoRate1),
    //LFO1 OSC1 ADSR & Gain
    attack1AT(apvts, "lfo1attack1", attack1), decay1AT(apvts, "lfo1decay1", decay1), sustain1AT(apvts, "lfo1sustain1", sustain1), release1AT(apvts, "lfo1release1", release1), gain1AT(apvts, "lfo1oscGain1", gain1),
    //LFO1 OSC2 ADSR & Gain
    attack2AT(apvts, "lfo1attack2", attack2), decay2AT(apvts, "lfo1decay2", decay2), sustain2AT(apvts, "lfo1sustain2", sustain2), release2AT(apvts, "lfo1release2", release2), gain2AT(apvts, "lfo1oscGain2", gain2),
    //LFO 1 Phaser Params
    rateAT(apvts, "lfo1phaserRate", rate), depthAT(apvts, "lfo1phaserDepth", depth), centerFreqAT(apvts, "lfo1phaserCenterFreq", centerFreq), pFeedbackAT(apvts, "lfo1phaserFeedback", pFeedback), pMixAT(apvts, "lfo1phaserMix", pMix)
{

    setLookAndFeel(&lnf);

    addAndMakeVisible(sine);
    addAndMakeVisible(saw);
    addAndMakeVisible(square);
    addAndMakeVisible(triangle);
    setSlider(lfoRate1);

    sine.onClick = [this] {updateToggleState(&sine); };
    saw.onClick = [this] {updateToggleState(&saw); };
    square.onClick = [this] {updateToggleState(&square); };
    triangle.onClick = [this] {updateToggleState(&triangle); };

    sine.setRadioGroupId(1);
    saw.setRadioGroupId(1);
    square.setRadioGroupId(1);
    triangle.setRadioGroupId(1);
    
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

    comboChange.onValueChange = [this]()
        {
            if (comboChange.getValue() == 1)
            {
                cutoff.setVisible(true);
                resonance.setVisible(true);
                drive.setVisible(true);

                rate.setVisible(false);
                depth.setVisible(false);
                centerFreq.setVisible(false);
                pFeedback.setVisible(false);
                pMix.setVisible(false);

                freq.setVisible(false);
                cFeedback.setVisible(false);
                cGain.setVisible(false);
                cMix.setVisible(false);
            }
            else if (comboChange.getValue() == 2)
            {
                cutoff.setVisible(false);
                resonance.setVisible(false);
                drive.setVisible(false);

                rate.setVisible(true);
                depth.setVisible(true);
                centerFreq.setVisible(true);
                pFeedback.setVisible(true);
                pMix.setVisible(true);

                freq.setVisible(false);
                cFeedback.setVisible(false);
                cGain.setVisible(false);
                cMix.setVisible(false);
            }
            else
            {
                cutoff.setVisible(false);
                resonance.setVisible(false);
                drive.setVisible(false);

                rate.setVisible(false);
                depth.setVisible(false);
                centerFreq.setVisible(false);
                pFeedback.setVisible(false);
                pMix.setVisible(false);

                freq.setVisible(true);
                cFeedback.setVisible(true);
                cGain.setVisible(true);
                cMix.setVisible(true);
            }
        };

    setGroupComp(Osc1);
    setGroupComp(Osc2);
    setGroupComp(Filter);
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

    //g.drawRect(adsr1Area.toFloat());

}

void LFOComp::resized()
{
    auto bounds = getLocalBounds();
    auto leftBounds = bounds.removeFromLeft(bounds.getWidth() * .5).reduced(10);
    auto rightBounds = bounds.reduced(10);

    setLeft(leftBounds);
}

void LFOComp::setSlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 1, 1);
    slider.setTooltip(slider.getName());
    addAndMakeVisible(slider);
}

void LFOComp::setRotarySlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 1, 1);
    slider.setTooltip(slider.getName());
    addAndMakeVisible(slider);
}

void LFOComp::setGroupComp(juce::GroupComponent& group)
{
    addAndMakeVisible(group);
    group.setText(group.getText());
    lnf.setColour(0x1005400, juce::Colours::cyan);
}

void LFOComp::setLeft(juce::Rectangle<int>& bounds)
{
    auto buttonArea = bounds.removeFromLeft(bounds.getHeight() * .15);
    auto adsr1Area = bounds.removeFromTop(bounds.getHeight() * .33);
    auto adsr2Area = bounds.removeFromTop(bounds.getHeight() * .5);
    auto filterAreaLadder = bounds;
    auto filterAreaPhaser = bounds;
    auto filterAreaComb = bounds;

    juce::FlexBox flexbox;
    flexbox.flexDirection = juce::FlexBox::Direction::column;
    flexbox.flexWrap = juce::FlexBox::Wrap::noWrap;

    flexbox.items.add(juce::FlexItem(sine).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(saw).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(square).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(triangle).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(lfoRate1).withFlex(1.f));
    flexbox.performLayout(buttonArea);

    flexbox.flexDirection = juce::FlexBox::Direction::row;

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

    auto cutoffArea = filterAreaLadder.removeFromLeft(filterAreaLadder.getWidth() * .33);
    cutoff.setBounds(cutoffArea);
    auto resArea = filterAreaLadder.removeFromLeft(filterAreaLadder.getWidth() * .5);
    resonance.setBounds(resArea);
    auto driveArea = filterAreaLadder.removeFromLeft(filterAreaLadder.getWidth());
    drive.setBounds(driveArea);

    auto rateArea = filterAreaPhaser.removeFromLeft(filterAreaPhaser.getWidth() * .2);
    rate.setBounds(rateArea);
    auto depthArea = filterAreaPhaser.removeFromLeft(filterAreaPhaser.getWidth() * .25);
    depth.setBounds(depthArea);
    auto centerFreqArea = filterAreaPhaser.removeFromLeft(filterAreaPhaser.getWidth() * .33);
    centerFreq.setBounds(centerFreqArea);
    auto feedbackArea = filterAreaPhaser.removeFromLeft(filterAreaPhaser.getWidth() * .5);
    pFeedback.setBounds(feedbackArea);
    auto mixArea = filterAreaPhaser.removeFromLeft(filterAreaPhaser.getWidth());
    pMix.setBounds(mixArea);

    auto freqAreaComb = filterAreaComb.removeFromLeft(filterAreaComb.getWidth() * .25);
    freq.setBounds(freqAreaComb);
    auto feedbackAreaComb = filterAreaComb.removeFromLeft(filterAreaComb.getWidth() * .33);
    cFeedback.setBounds(feedbackAreaComb);
    auto gainAreaComb = filterAreaComb.removeFromLeft(filterAreaComb.getWidth() * .5);
    cGain.setBounds(gainAreaComb);
    auto mixAreaComb = filterAreaComb.removeFromLeft(filterAreaComb.getWidth());
    cMix.setBounds(mixAreaComb);

    /*if (cutoff.isVisible())
    {
        flexbox.items.clear();
        flexbox.items.add(juce::FlexItem(cutoff).withFlex(1.f));
        flexbox.items.add(juce::FlexItem(resonance).withFlex(1.f));
        flexbox.items.add(juce::FlexItem(drive).withFlex(1.f));
    }
    else if (rate.isVisible())
    {
        flexbox.items.clear();
        flexbox.items.add(juce::FlexItem(rate).withFlex(1.f));
        flexbox.items.add(juce::FlexItem(depth).withFlex(1.f));
        flexbox.items.add(juce::FlexItem(centerFreq).withFlex(1.f));
        flexbox.items.add(juce::FlexItem(pFeedback).withFlex(1.f));
        flexbox.items.add(juce::FlexItem(pMix).withFlex(1.f));
    }
    else if(freq.isVisible())
    {
        flexbox.items.clear();
        flexbox.items.add(juce::FlexItem(freq).withFlex(1.f));
        flexbox.items.add(juce::FlexItem(cFeedback).withFlex(1.f));
        flexbox.items.add(juce::FlexItem(cGain).withFlex(1.f));
        flexbox.items.add(juce::FlexItem(cMix).withFlex(1.f));
    }

    flexbox.performLayout(filterArea);*/

    Osc1.setBounds(adsr1Area.getX(), adsr1Area.getY() - 5, adsr1Area.getWidth(), adsr1Area.getHeight());
    Osc2.setBounds(adsr2Area.getX(), adsr2Area.getY() - 5, adsr2Area.getWidth(), adsr2Area.getHeight());
    Filter.setBounds(bounds.getX(), bounds.getY() - 5, bounds.getWidth(), bounds.getHeight());
}

void LFOComp::updateToggleState(juce::Button* button)
{
    auto state = button->getToggleState();
}

void LFOComp::getComboValue(int combo)
{
    comboChange.setValue(combo);
}
