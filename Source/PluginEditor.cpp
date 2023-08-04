/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleSynthAudioProcessorEditor::SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(oscComp1);
    addAndMakeVisible(oscComp2);

    setSize (1000, 800);
}

SimpleSynthAudioProcessorEditor::~SimpleSynthAudioProcessorEditor()
{
}

//==============================================================================
void SimpleSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    auto bounds = getLocalBounds();
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);

    auto globalControls = bounds.removeFromTop(bounds.getHeight() * .05);
    g.drawRect(globalControls);
    g.drawFittedText("Global Controls", globalControls, juce::Justification::centred, 1);

    auto filter = bounds.removeFromTop(bounds.getHeight() * .47);
    auto oscs = filter.removeFromLeft(bounds.getWidth() * .66);
    g.drawRect(filter);
    g.drawFittedText("Filter", filter, juce::Justification::centred, 1);
    g.drawRect(oscs);
    //g.drawFittedText("Oscilators", oscs, juce::Justification::centred, 1);

    auto lfos = bounds.removeFromTop(bounds.getHeight() * .7);
    g.drawRect(lfos);
    g.drawFittedText("LFO's", lfos, juce::Justification::centred, 1);

    auto keyboard = bounds;
    g.drawRect(keyboard);
    g.drawFittedText("Keyboard", keyboard, juce::Justification::centred, 1);

}

void SimpleSynthAudioProcessorEditor::resized()
{

    auto bounds = getLocalBounds();
    
    auto globalControlsBounds = bounds.removeFromTop(bounds.getHeight() * .05);

    auto filterBounds = bounds.removeFromTop(bounds.getHeight() * .47);

    auto oscsBounds = filterBounds.removeFromLeft(filterBounds.getWidth() * .66);
    auto osc1Bounds = oscsBounds.removeFromLeft(oscsBounds.getWidth() * .5);
    oscComp1.setBounds(osc1Bounds);
    oscComp2.setBounds(oscsBounds);

    auto lfosBounds = bounds.removeFromTop(bounds.getHeight() * .7);

    auto keyboardBounds = bounds;

}
