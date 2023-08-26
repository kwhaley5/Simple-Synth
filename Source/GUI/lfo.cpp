/*
  ==============================================================================

    lfo.cpp
    Created: 17 Aug 2023 4:14:19pm
    Author:  kylew

  ==============================================================================
*/

#include "lfo.h"

LFOComp::LFOComp(juce::AudioProcessorValueTreeState& apvts) :
    //LFO 2 type and RAte
    sineAT(apvts, "lfo1sine", sine), sawAT(apvts, "lfo1saw", saw), squareAT(apvts, "lfo1square", square), triangleAT(apvts, "lfo1triangle", triangle), lfoRate1AT(apvts, "lfo1Rate", lfoRate1),
    //LFO1 OSC1 ADSR & Gain
    attack1AT(apvts, "lfo1attack1", attack1), decay1AT(apvts, "lfo1decay1", decay1), sustain1AT(apvts, "lfo1sustain1", sustain1), release1AT(apvts, "lfo1release1", release1), gain1AT(apvts, "lfo1oscGain1", gain1),
    //LFO1 OSC2 ADSR & Gain
    attack2AT(apvts, "lfo1attack2", attack2), decay2AT(apvts, "lfo1decay2", decay2), sustain2AT(apvts, "lfo1sustain2", sustain2), release2AT(apvts, "lfo1release2", release2), gain2AT(apvts, "lfo1oscGain2", gain2),
    //LFO 1 Ladder Params
    cutoffAT(apvts, "lfo1ladderFreq", cutoff), resonanceAT(apvts, "lfo1ladderRes", resonance), driveAT(apvts, "lfo1ladderDrive", drive),
    //LFO 1 Phaser Params
    rateAT(apvts, "lfo1phaserRate", rate), depthAT(apvts, "lfo1phaserDepth", depth), centerFreqAT(apvts, "lfo1phaserCenterFreq", centerFreq), pFeedbackAT(apvts, "lfo1phaserFeedback", pFeedback), pMixAT(apvts, "lfo1phaserMix", pMix),
    //LFO 1 Comb Parms
    freqAT(apvts, "lfo1combFreq", freq), cFeedbackAT(apvts, "lfo1combFeedback", cFeedback), cGainAT(apvts, "lfo1combGain", cGain), cMixAT(apvts, "lfo1combMix", cMix),
    //LFO 2 type and RAte
    sine2AT(apvts, "lfo2sine", sine2), saw2AT(apvts, "lfo2saw", saw2), square2AT(apvts, "lfo2square", square2), triangle2AT(apvts, "lfo2triangle", triangle2), lfoRate2AT(apvts, "lfo2Rate", lfoRate2),
    //LFO2 OSC1 ADSR & Gain
    attack12AT(apvts, "lfo2attack1", attack12), decay12AT(apvts, "lfo2decay1", decay12), sustain12AT(apvts, "lfo2sustain1", sustain12), release12AT(apvts, "lfo2release1", release12), gain12AT(apvts, "lfo2oscGain1", gain12),
    //LFO2 OSC2 ADSR & Gain
    attack22AT(apvts, "lfo2attack2", attack22), decay22AT(apvts, "lfo2decay2", decay22), sustain22AT(apvts, "lfo2sustain2", sustain22), release22AT(apvts, "lfo2release2", release22), gain22AT(apvts, "lfo2oscGain2", gain22),
    //LFO 2 Ladder Params
    cutoff2AT(apvts, "lfo2ladderFreq", cutoff2), resonance2AT(apvts, "lfo2ladderRes", resonance2), drive2AT(apvts, "lfo2ladderDrive", drive2),
    //LFO 2 Phaser Params
    rate2AT(apvts, "lfo2phaserRate", rate2), depth2AT(apvts, "lfo2phaserDepth", depth2), centerFreq2AT(apvts, "lfo2phaserCenterFreq", centerFreq2), pFeedback2AT(apvts, "lfo2phaserFeedback", pFeedback2), pMix2AT(apvts, "lfo2phaserMix", pMix2),
    //LFO 2 Comb Parms
    freq2AT(apvts, "lfo2combFreq", freq2), cFeedback2AT(apvts, "lfo2combFeedback", cFeedback2), cGain2AT(apvts, "lfo2combGain", cGain2), cMix2AT(apvts, "lfo2combMix", cMix2)
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

    setGroupComp(Osc1);
    setGroupComp(Osc2);
    setGroupComp(Filter);

    addAndMakeVisible(sine2);
    addAndMakeVisible(saw2);
    addAndMakeVisible(square2);
    addAndMakeVisible(triangle2);
    setSlider(lfoRate2);

    sine2.onClick = [this] {updateToggleState(&sine2); };
    saw2.onClick = [this] {updateToggleState(&saw2); };
    square2.onClick = [this] {updateToggleState(&square2); };
    triangle2.onClick = [this] {updateToggleState(&triangle2); };

    sine2.setRadioGroupId(2);
    saw2.setRadioGroupId(2);
    square2.setRadioGroupId(2);
    triangle2.setRadioGroupId(2);

    setRotarySlider(attack12);
    setRotarySlider(decay12);
    setRotarySlider(sustain12);
    setRotarySlider(release12);

    setRotarySlider(attack22);
    setRotarySlider(decay22);
    setRotarySlider(sustain22);
    setRotarySlider(release22);

    setRotarySlider(gain12);
    setRotarySlider(gain22);

    setRotarySlider(cutoff2);
    setRotarySlider(resonance2);
    setRotarySlider(drive2);

    setRotarySlider(rate2);
    setRotarySlider(depth2);
    setRotarySlider(centerFreq2);
    setRotarySlider(pFeedback2);
    setRotarySlider(pMix2);

    setRotarySlider(freq2);
    setRotarySlider(cFeedback2);
    setRotarySlider(cGain2);
    setRotarySlider(cMix2);

    setGroupComp(Osc12);
    setGroupComp(Osc22);
    setGroupComp(Filter2);

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

                cutoff2.setVisible(true);
                resonance2.setVisible(true);
                drive2.setVisible(true);

                rate2.setVisible(false);
                depth2.setVisible(false);
                centerFreq2.setVisible(false);
                pFeedback2.setVisible(false);
                pMix2.setVisible(false);

                freq2.setVisible(false);
                cFeedback2.setVisible(false);
                cGain2.setVisible(false);
                cMix2.setVisible(false);
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

                cutoff2.setVisible(false);
                resonance2.setVisible(false);
                drive2.setVisible(false);

                rate2.setVisible(true);
                depth2.setVisible(true);
                centerFreq2.setVisible(true);
                pFeedback2.setVisible(true);
                pMix2.setVisible(true);

                freq2.setVisible(false);
                cFeedback2.setVisible(false);
                cGain2.setVisible(false);
                cMix2.setVisible(false);
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

                cutoff2.setVisible(false);
                resonance2.setVisible(false);
                drive2.setVisible(false);

                rate2.setVisible(false);
                depth2.setVisible(false);
                centerFreq2.setVisible(false);
                pFeedback2.setVisible(false);
                pMix2.setVisible(false);

                freq2.setVisible(true);
                cFeedback2.setVisible(true);
                cGain2.setVisible(true);
                cMix2.setVisible(true);
            }
        };
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
    setRight(rightBounds);
}

void LFOComp::setSlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 1, 1);
    slider.setTooltip("Hz");
    addAndMakeVisible(slider);
}

void LFOComp::setRotarySlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 1, 1);
    slider.setTooltip(slider.getName());
    slider.setComponentID("LFO");
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

    Osc1.setBounds(adsr1Area.getX(), adsr1Area.getY() - 5, adsr1Area.getWidth(), adsr1Area.getHeight());
    Osc2.setBounds(adsr2Area.getX(), adsr2Area.getY() - 5, adsr2Area.getWidth(), adsr2Area.getHeight());
    Filter.setBounds(bounds.getX(), bounds.getY() - 5, bounds.getWidth(), bounds.getHeight());
}

void LFOComp::setRight(juce::Rectangle<int>& bounds)
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

    flexbox.items.add(juce::FlexItem(sine2).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(saw2).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(square2).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(triangle2).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(lfoRate2).withFlex(1.f));
    flexbox.performLayout(buttonArea);

    flexbox.flexDirection = juce::FlexBox::Direction::row;

    flexbox.items.clear();
    flexbox.items.add(juce::FlexItem(attack12).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(decay12).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(sustain12).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(release12).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(gain12).withFlex(1.f));
    flexbox.performLayout(adsr1Area);

    flexbox.items.clear();
    flexbox.items.add(juce::FlexItem(attack22).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(decay22).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(sustain22).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(release22).withFlex(1.f));
    flexbox.items.add(juce::FlexItem(gain22).withFlex(1.f));
    flexbox.performLayout(adsr2Area);

    auto cutoffArea = filterAreaLadder.removeFromLeft(filterAreaLadder.getWidth() * .33);
    cutoff2.setBounds(cutoffArea);
    auto resArea = filterAreaLadder.removeFromLeft(filterAreaLadder.getWidth() * .5);
    resonance2.setBounds(resArea);
    auto driveArea = filterAreaLadder.removeFromLeft(filterAreaLadder.getWidth());
    drive2.setBounds(driveArea);

    auto rateArea = filterAreaPhaser.removeFromLeft(filterAreaPhaser.getWidth() * .2);
    rate2.setBounds(rateArea);
    auto depthArea = filterAreaPhaser.removeFromLeft(filterAreaPhaser.getWidth() * .25);
    depth2.setBounds(depthArea);
    auto centerFreqArea = filterAreaPhaser.removeFromLeft(filterAreaPhaser.getWidth() * .33);
    centerFreq2.setBounds(centerFreqArea);
    auto feedbackArea = filterAreaPhaser.removeFromLeft(filterAreaPhaser.getWidth() * .5);
    pFeedback2.setBounds(feedbackArea);
    auto mixArea = filterAreaPhaser.removeFromLeft(filterAreaPhaser.getWidth());
    pMix2.setBounds(mixArea);

    auto freqAreaComb = filterAreaComb.removeFromLeft(filterAreaComb.getWidth() * .25);
    freq2.setBounds(freqAreaComb);
    auto feedbackAreaComb = filterAreaComb.removeFromLeft(filterAreaComb.getWidth() * .33);
    cFeedback2.setBounds(feedbackAreaComb);
    auto gainAreaComb = filterAreaComb.removeFromLeft(filterAreaComb.getWidth() * .5);
    cGain2.setBounds(gainAreaComb);
    auto mixAreaComb = filterAreaComb.removeFromLeft(filterAreaComb.getWidth());
    cMix2.setBounds(mixAreaComb);

    Osc12.setBounds(adsr1Area.getX(), adsr1Area.getY() - 5, adsr1Area.getWidth(), adsr1Area.getHeight());
    Osc22.setBounds(adsr2Area.getX(), adsr2Area.getY() - 5, adsr2Area.getWidth(), adsr2Area.getHeight());
    Filter2.setBounds(bounds.getX(), bounds.getY() - 5, bounds.getWidth(), bounds.getHeight());
}

void LFOComp::updateToggleState(juce::Button* button)
{
    auto state = button->getToggleState();
}

void LFOComp::getComboValue(int combo)
{
    comboChange.setValue(combo);
}
