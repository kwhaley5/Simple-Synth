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
    addAndMakeVisible(globalControls);
    addAndMakeVisible(lfoComp);

    setKeyboard();

    setSize (1000, 800);
    startTimerHz(24);
}

SimpleSynthAudioProcessorEditor::~SimpleSynthAudioProcessorEditor()
{
}

//==============================================================================
void SimpleSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    auto grad = juce::ColourGradient::ColourGradient(juce::Colour(186u, 34u, 34u), bounds.toFloat().getTopLeft(), juce::Colour(186u, 34u, 34u), bounds.toFloat().getBottomRight(), false);
    grad.addColour(.33f, juce::Colours::transparentBlack);
    grad.addColour(.5f, juce::Colour(186u, 34u, 34u));
    grad.addColour(.66f, juce::Colours::transparentBlack);

    g.setGradientFill(grad);
    //g.fillAll (juce::Colour(50u,30u,30u)); //create background
    g.fillAll();

    //auto bounds = getLocalBounds();
    g.setColour(juce::Colours::red);
    g.setFont(15.0f);

    auto globalControls = bounds.removeFromTop(bounds.getHeight() * .05);
    g.drawRect(globalControls);
    //g.drawFittedText("Global Controls", globalControls, juce::Justification::centred, 1);

    auto filter = bounds.removeFromTop(bounds.getHeight() * .47);
    auto oscs = filter.removeFromLeft(bounds.getWidth() * .66);
    g.drawRect(filter);
    //g.drawFittedText("Filter", filter, juce::Justification::centred, 1);
    g.drawRect(oscs);
    //g.drawFittedText("Oscilators", oscs, juce::Justification::centred, 1);

    auto lfos = bounds.removeFromTop(bounds.getHeight() * .7);
    g.drawRect(lfos);
    //g.drawFittedText("LFO's", lfos, juce::Justification::centred, 1);

    auto keyboard = bounds;
    g.drawRect(keyboard.getX(), keyboard.getY(), keyboard.getWidth(), keyboard.getHeight() + 2);
    //g.drawFittedText("Keyboard", keyboard, juce::Justification::centred, 1);

    setColour(0x1005004, juce::Colour(64u, 194u, 230u));

}

void SimpleSynthAudioProcessorEditor::resized()
{

    auto bounds = getLocalBounds();
    
    auto globalControlsBounds = bounds.removeFromTop(bounds.getHeight() * .05);
    globalControls.setBounds(globalControlsBounds);

    auto filterBounds = bounds.removeFromTop(bounds.getHeight() * .47);
    auto oscsBounds = filterBounds.removeFromLeft(filterBounds.getWidth() * .66);
    oscComp.setBounds(oscsBounds);
    filterComp.setBounds(filterBounds);

    auto lfosBounds = bounds.removeFromTop(bounds.getHeight() * .7);
    lfoComp.setBounds(lfosBounds);

    setColour(0x1005004, juce::Colour(64u, 194u, 230u));
    auto keyboardBounds = bounds;
    keyboard.setBounds(keyboardBounds);

}

void SimpleSynthAudioProcessorEditor::timerCallback()
{
    std::vector<float> values
    {
        audioProcessor.getOutRMS(0),
        audioProcessor.getOutRMS(1)
    };

    globalControls.update(values);
    lfoComp.getComboValue(filterComp.getComboValue());   
}

void SimpleSynthAudioProcessorEditor::setKeyboard()
{
    auto lnf = &getLookAndFeel();

    keyboard.setKeyWidth(25);
    addAndMakeVisible(keyboard);

    lnf->setColour(0x1005003, juce::Colour(64u, 194u, 230u));
    lnf->setColour(0x1005004, juce::Colour(64u, 194u, 230u));
}
