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
    addAndMakeVisible(oscComp);
    addAndMakeVisible(filterComp);

    keyboard.setKeyWidth(20);
    addAndMakeVisible(keyboard);

    setSize (1000, 800);
}

SimpleSynthAudioProcessorEditor::~SimpleSynthAudioProcessorEditor()
{
}

//==============================================================================
void SimpleSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
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
    //g.drawFittedText("Filter", filter, juce::Justification::centred, 1);
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
    oscComp.setBounds(oscsBounds);
    filterComp.setBounds(filterBounds);

    auto lfosBounds = bounds.removeFromTop(bounds.getHeight() * .7);

    auto keyboardBounds = bounds;
    keyboard.setBounds(keyboardBounds);

}

void SimpleSynthAudioProcessorEditor::setKeyboard()
{
    keyboard.setKeyWidth(25);
    addAndMakeVisible(keyboard);

    auto bounds = getLocalBounds();

    auto keyboardBounds = bounds.removeFromBottom(bounds.getHeight() * .2);
    keyboard.setBounds(keyboardBounds);
}
