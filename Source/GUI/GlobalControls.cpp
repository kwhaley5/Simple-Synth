/*
  ==============================================================================

    GlobalControls.cpp
    Created: 17 Aug 2023 8:57:12am
    Author:  kylew

  ==============================================================================
*/

#include "GlobalControls.h"

GlobalControls::GlobalControls(juce::AudioProcessorValueTreeState& apvts) :
    bypass1AT(apvts, "bypassSynth1", bypass1), bypass2AT(apvts, "bypassSynth2", bypass2), 
    bypassFilterAT(apvts, "bypassFilter", bypassFilter), gainAT(apvts, "gGain", globalGain)
{
    setLookAndFeel(&lnf);
    addAndMakeVisible(outMeter[0]);
    addAndMakeVisible(outMeter[1]);

    setRotarySlider(globalGain);

    addAndMakeVisible(bypass1);
    bypass1.setComponentID("Power");
    addAndMakeVisible(bypass2);
    bypass2.setComponentID("Power");
    addAndMakeVisible(bypassFilter);
    bypassFilter.setComponentID("Power");

}

GlobalControls::~GlobalControls()
{
    setLookAndFeel(nullptr);
}

void GlobalControls::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    auto logoArea = bounds.removeFromLeft(bounds.getWidth() * .2).reduced(5);

    auto simpleArea = logoArea.removeFromLeft(logoArea.getWidth() * .4);
    auto maskArea = logoArea.removeFromLeft(logoArea.getWidth() * .33);
    auto synthArea = logoArea.removeFromLeft(logoArea.getWidth());

    auto logo = juce::ImageCache::getFromMemory(BinaryData::KITIK_LOGO_NO_BKGD_png, BinaryData::KITIK_LOGO_NO_BKGD_pngSize);
    //g.drawImage(logo, maskArea.toFloat());
    g.drawImage(logo, maskArea.toFloat(), juce::RectanglePlacement::fillDestination);

    auto newFont = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::OFFSHORE_TTF, BinaryData::OFFSHORE_TTFSize));
    g.setColour(juce::Colours::whitesmoke);
    g.setFont(newFont);
    g.setFont(30.f);
    g.drawFittedText("Simple", simpleArea, juce::Justification::centredRight, 1);
    g.drawFittedText("Synth", synthArea, juce::Justification::centredLeft, 1);

    auto synth1Area = bounds.removeFromLeft(bounds.getWidth() * .17);
    g.setFont(juce::Font::Font());
    g.drawFittedText(bypass1.getName(), synth1Area, juce::Justification::right, 1);

    auto synth2Area = bounds.removeFromLeft(bounds.getWidth() * .21);
    g.drawFittedText(bypass2.getName(), synth2Area, juce::Justification::right, 1);

    auto filterArea = bounds.removeFromRight(bounds.getWidth() * .48);
    g.drawFittedText(bypassFilter.getName(), filterArea, juce::Justification::left, 1);

    //g.drawRect(bounds, 1);
}

void GlobalControls::resized()
{
    auto bounds = getLocalBounds();

    juce::FlexBox flexBox;
    flexBox.flexDirection = juce::FlexBox::Direction::row;
    flexBox.flexWrap = juce::FlexBox::Wrap::noWrap;

    auto logo = juce::FlexItem();
    auto deadSpace = juce::FlexItem();
    //auto Meters = juce::FlexItem();

    flexBox.items.add(logo.withFlex(2.f));
    flexBox.items.add(juce::FlexItem(bypass1).withFlex(1.f));
    flexBox.items.add(juce::FlexItem(bypass2).withFlex(2.f));
    flexBox.items.add(deadSpace.withFlex(2.5f));
    flexBox.items.add(juce::FlexItem(bypassFilter).withFlex(1.f));
    flexBox.items.add(juce::FlexItem(globalGain).withFlex(2.f));
    flexBox.items.add(juce::FlexItem(outMeter[0]).withFlex(.25));
    flexBox.items.add(juce::FlexItem(outMeter[1]).withFlex(.25));

    flexBox.performLayout(bounds);
}

void GlobalControls::setRotarySlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 1, 1);
    slider.setComponentID("gGain");
    addAndMakeVisible(slider);
}

void GlobalControls::update(const std::vector<float> &values)
{
    enum
    {
        left,
        right
    };

    outMeter[0].setLevel(values[left]);
    outMeter[1].setLevel(values[right]);

    outMeter[0].repaint();
    outMeter[1].repaint();
}
