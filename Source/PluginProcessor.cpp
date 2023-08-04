/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleSynthAudioProcessor::SimpleSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    synth1.addSound(new SynthSound());
    synth1.addVoice(new SynthVoice());

    synth2.addSound(new SynthSound());
    synth2.addVoice(new SynthVoice());

    attack1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("attack1"));
    decay1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("decay1"));
    sustain1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("sustain1"));
    release1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("release1"));
    oscGain1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("oscGain1"));
    sine1 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("sine1"));
    saw1 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("saw1"));
    square1 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("square1"));
    triangle1 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("triangle1"));

    attack2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("attack2"));
    decay2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("decay2"));
    sustain2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("sustain2"));
    release2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("release2"));
    oscGain2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("oscGain2"));
    sine2 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("sine2"));
    saw2 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("saw2"));
    square2 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("square2"));
    triangle2 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("triangle2"));
}

SimpleSynthAudioProcessor::~SimpleSynthAudioProcessor()
{
}

//==============================================================================
const juce::String SimpleSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SimpleSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth1.setCurrentPlaybackSampleRate(sampleRate);
    synth2.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < synth1.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth1.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }

    for (int i = 0; i < synth2.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth2.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void SimpleSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    wavetype1[0] = sine1->get();
    wavetype1[1] = saw1->get();
    wavetype1[2] = square1->get();
    wavetype1[3] = triangle1->get();

    wavetype2[0] = sine2->get();
    wavetype2[1] = saw2->get();
    wavetype2[2] = square2->get();
    wavetype2[3] = triangle2->get();

    for (int i = 0; i < synth1.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth1.getVoice(i)))
        {
            voice->getOscillator().setWaveType(wavetype1);
        }
    }

    synth1.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    synth2.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SimpleSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleSynthAudioProcessor::createEditor()
{
    return new SimpleSynthAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void SimpleSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);

}

void SimpleSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid()) {
        apvts.replaceState(tree);
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout SimpleSynthAudioProcessor::createParameterLayout()
{
    using namespace juce;
    AudioProcessorValueTreeState::ParameterLayout layout;

    auto range = NormalisableRange<float>(0, 5, .001, .7);
    auto susRange = NormalisableRange<float>(0, 1, .01, 1);
    auto gainRange = NormalisableRange<float>(-60, 6, .1, 1);

    //Global Toggle Switch
    //Global Gain Ouput

    //osc 1 
    layout.add(std::make_unique<AudioParameterBool>("sine1", "Osc 1 Sine Wave", true));
    layout.add(std::make_unique<AudioParameterBool>("saw1", "Osc 1 Saw Wave", false));
    layout.add(std::make_unique<AudioParameterBool>("square1", "Osc 1 Square Wave", false));
    layout.add(std::make_unique<AudioParameterBool>("triangle1", "Osc 1 Triangle Wave", false));

    layout.add(std::make_unique<AudioParameterFloat>("attack1", "Osc 1 Attack", range, .05));
    layout.add(std::make_unique<AudioParameterFloat>("decay1", "Osc 1 Decay", range, .05));
    layout.add(std::make_unique<AudioParameterFloat>("sustain1", "Osc 1 Sustain", susRange, 1));
    layout.add(std::make_unique<AudioParameterFloat>("release1", "Osc 1 Release", range, .05));
    layout.add(std::make_unique<AudioParameterFloat>("oscGain1", "Osc 1 Gain", gainRange, -6));

    //osc 2
    layout.add(std::make_unique<AudioParameterBool>("sine2", "Osc 2 Sine Wave", true));
    layout.add(std::make_unique<AudioParameterBool>("saw2", "Osc 2 Saw Wave", false));
    layout.add(std::make_unique<AudioParameterBool>("square2", "Osc 2 Square Wave", false));
    layout.add(std::make_unique<AudioParameterBool>("triangle2", "Osc 2 Triangle Wave", false));

    layout.add(std::make_unique<AudioParameterFloat>("attack2", "Osc 2 Attack", range, .05));
    layout.add(std::make_unique<AudioParameterFloat>("decay2", "Osc 2 Decay", range, .05));
    layout.add(std::make_unique<AudioParameterFloat>("sustain2", "Osc 2 Sustain", susRange, .5));
    layout.add(std::make_unique<AudioParameterFloat>("release2", "Osc 2 Release", range, .05));
    layout.add(std::make_unique<AudioParameterFloat>("oscGain2", "Osc 2 Gain", gainRange, -6));

    //FM Freq
    //FM Depth

    //Filter
    //Ladder Filter
        //Freq
        //res
        //drive
        //mix?
    //comb
        //freq
        //res
        //mix?
    //Phaser
        //rate
        // centreFreq
        // feedback
        // mix
        //depth

    //LFO's
        //Rate
        //Amplitude
        //Set Same types as osc
        //Figure out how to link stuff... Try looking at Surge.

    //juce MidiKeyboardComponent
        //juce keyboard
        //pitch wheel -> no juce object, look that up too
        //mod wheel



    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleSynthAudioProcessor();
}
