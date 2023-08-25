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
    synth1.addVoice(new SynthVoice());
    synth1.addVoice(new SynthVoice());
    synth1.addVoice(new SynthVoice());

    synth2.addSound(new SynthSound());
    synth2.addVoice(new SynthVoice());
    synth2.addVoice(new SynthVoice());
    synth2.addVoice(new SynthVoice());
    synth2.addVoice(new SynthVoice());

    //Global Controls
    gGain = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("gGain"));
    bypassSynth1 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("bypassSynth1"));
    bypassSynth2 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("bypassSynth2"));
    bypassFilter = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("bypassFilter"));

    voices = dynamic_cast<juce::AudioParameterInt*>(apvts.getParameter("voices"));

    //Osc 1
    attack1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("attack1"));
    decay1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("decay1"));
    sustain1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("sustain1"));
    release1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("release1"));
    oscGain1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("oscGain1"));
    sine1 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("sine1"));
    saw1 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("saw1"));
    square1 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("square1"));
    triangle1 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("triangle1"));

    //Osc 2
    attack2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("attack2"));
    decay2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("decay2"));
    sustain2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("sustain2"));
    release2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("release2"));
    oscGain2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("oscGain2"));
    sine2 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("sine2"));
    saw2 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("saw2"));
    square2 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("square2"));
    triangle2 = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("triangle2"));

    //fm params
    fmOsc = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("fmOsc"));
    fmDepth = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("fmDepth"));

    filterType = dynamic_cast<juce::AudioParameterChoice*>(apvts.getParameter("filterType"));

    //Ladder Params
    ladderChoice = dynamic_cast<juce::AudioParameterChoice*>(apvts.getParameter("ladderChoice"));
    ladderFreq = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("ladderFreq"));
    ladderRes = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("ladderRes"));
    ladderDrive = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("ladderDrive"));

    //Phaser Params
    phaserRate = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("phaserRate"));
    phaserDepth = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("phaserDepth"));
    phaserCenterFreq = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("phaserCenterFreq"));
    phaserFeedback = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("phaserFeedback"));
    phaserMix = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("phaserMix"));

    //Comb Params
    combFreq = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("combFreq"));
    combFeedback = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("combFeedback"));
    combGain = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("combGain"));
    combMix = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("combMix"));

    //LFO1 Wave Type
    lfo1sine = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("lfo1sine"));
    lfo1saw = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("lfo1saw"));
    lfo1square = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("lfo1square"));
    lfo1triangle = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("lfo1triangle"));

    //LFO 1 Params
    lfo1attack1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1attack1"));
    lfo1decay1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1decay1"));
    lfo1sustain1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1sustain1"));
    lfo1release1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1release1"));
    lfo1oscGain1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1oscGain1"));

    lfo1attack2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1attack2"));
    lfo1decay2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1decay2"));
    lfo1sustain2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1sustain2"));
    lfo1release2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1release2"));
    lfo1oscGain2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1oscGain2"));

    lfo1ladderFreq = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1ladderFreq"));
    lfo1ladderRes = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1ladderRes"));
    lfo1ladderDrive = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1ladderDrive"));

    lfo1phaserRate = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1phaserRate"));
    lfo1phaserDepth = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1phaserDepth"));
    lfo1phaserCenterFreq = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1phaserCenterFreq"));
    lfo1phaserFeedback = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1phaserFeedback"));
    lfo1phaserMix = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1phaserMix"));

    lfo1combFreq = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1combFreq"));
    lfo1combFeedback = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1combFeedback"));
    lfo1combGain = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1combGain"));
    lfo1combMix = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1combMix"));

    lfo1Rate = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo1Rate"));

    //LFO1 Wave Type
    lfo2sine = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("lfo2sine"));
    lfo2saw = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("lfo2saw"));
    lfo2square = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("lfo2square"));
    lfo2triangle = dynamic_cast<juce::AudioParameterBool*>(apvts.getParameter("lfo2triangle"));

    //LFO 2 Params
    lfo2attack1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2attack1"));
    lfo2decay1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2decay1"));
    lfo2sustain1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2sustain1"));
    lfo2release1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2release1"));
    lfo2oscGain1 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2oscGain1"));

    lfo2attack2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2attack2"));
    lfo2decay2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2decay2"));
    lfo2sustain2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2sustain2"));
    lfo2release2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2release2"));
    lfo2oscGain2 = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2oscGain2"));

    lfo2ladderFreq = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2ladderFreq"));
    lfo2ladderRes = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2ladderRes"));
    lfo2ladderDrive = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2ladderDrive"));

    lfo2phaserRate = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2phaserRate"));
    lfo2phaserDepth = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2phaserDepth"));
    lfo2phaserCenterFreq = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2phaserCenterFreq"));
    lfo2phaserFeedback = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2phaserFeedback"));
    lfo2phaserMix = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2phaserMix"));

    lfo2combFreq = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2combFreq"));
    lfo2combFeedback = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2combFeedback"));
    lfo2combGain = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2combGain"));
    lfo2combMix = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2combMix"));

    lfo2Rate = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("lfo2Rate"));
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
    globalGain.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    filters.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    lfo1.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    lfo2.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
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
    keyState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    fillArrays();

    /*if (synth1.getNumVoices() < voices->get())
    {
        auto create = voices->get() - synth1.getNumVoices();
        for (int nVoice = 0; nVoice < create; nVoice++)
        {
            synth1.addVoice(new SynthVoice());
            //Need to figure out how to prepare voice after it is created
        }
    }
    else
    {
        auto destroy = synth1.getNumSounds() - voices->get();
        for (int nVoice = 0; nVoice < destroy; nVoice++)
        {
            synth1.removeVoice(nVoice);
        }

    }*/

    globalGain.setGain(gGain->get());

    setLFOs(buffer);

    for (int i = 0; i < synth1.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth1.getVoice(i)))
        {
            //voice->prepareToPlay(getSampleRate(), getBlockSize(), getTotalNumOutputChannels());
            voice->update(osc1Params[0], osc1Params[1], osc1Params[2], osc1Params[3], osc1Params[4]);
            voice->getOscillator().setWaveType(wavetype1);
            if(fmOsc->get())
                voice->getOscillator().setFmParams(synth1.getVoice(i)->getCurrentlyPlayingNote(), fmDepth->get(), wavetype2);
        }
    }

    for (int i = 0; i < synth2.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth2.getVoice(i)))
        {
            //voice->prepareToPlay(getSampleRate(), getBlockSize(), getTotalNumOutputChannels());
            voice->update(osc2Params[0], osc2Params[1], osc2Params[2], osc2Params[3], osc2Params[4]);
            voice->getOscillator().setWaveType(wavetype2);
        }
    }

    if(!bypassSynth1->get())
        synth1.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    if(!bypassSynth2->get() && !fmOsc->get())
        synth2.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    filters.updateLadderParams(ladderChoice->getIndex(), ladderParams[0], ladderParams[1], ladderParams[2]);
    filters.updatePhaserParams(phaserParams[0], phaserParams[1], phaserParams[2], phaserParams[3], phaserParams[4]);

    if (!bypassFilter->get())
    {
        filters.process(buffer);
        for (auto ch = 0; ch < buffer.getNumChannels(); ++ch)
            filters.processComb(ch, buffer, combParams[0], combParams[1], combParams[2], combParams[3], getSampleRate());
    }

    globalGain.processCtx(buffer);

    viz.pushBuffer(buffer);

    for (auto channel = 0; channel < totalNumOutputChannels; ++channel) 
    {
        rmsOut[channel] = juce::Decibels::gainToDecibels(buffer.getRMSLevel(channel, 0, buffer.getNumSamples()));
        if (rmsOut[channel] < -60) { rmsOut[channel] = -60; }
    }

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

void SimpleSynthAudioProcessor::fillArrays()
{
    //Select Osc 1 Wave Type
    wavetype1[0] = sine1->get();
    wavetype1[1] = saw1->get();
    wavetype1[2] = square1->get();
    wavetype1[3] = triangle1->get();

    //Select Osc 2 Wave Type
    wavetype2[0] = sine2->get();
    wavetype2[1] = saw2->get();
    wavetype2[2] = square2->get();
    wavetype2[3] = triangle2->get();

    //Select LFO 1 Wave Type
    setLFO1Wave[0] = lfo1sine->get();
    setLFO1Wave[1] = lfo1saw->get();
    setLFO1Wave[2] = lfo1square->get();
    setLFO1Wave[3] = lfo1triangle->get();

    //Select LFO 2 Wave Type
    setLFO2Wave[0] = lfo2sine->get();
    setLFO2Wave[1] = lfo2saw->get();
    setLFO2Wave[2] = lfo2square->get();
    setLFO2Wave[2] = lfo2triangle->get();

    //Set Osc 1 ADSR
    osc1Params[0] = attack1->get();
    osc1Params[1] = decay1->get();
    osc1Params[2] = sustain1->get();
    osc1Params[3] = release1->get();
    osc1Params[4] = oscGain1->get();

    //set Osc 2 ADSR
    osc2Params[0] = attack2->get();
    osc2Params[1] = decay2->get();
    osc2Params[2] = sustain2->get();
    osc2Params[3] = release2->get();
    osc2Params[4] = oscGain2->get();

    //set ladder for LFO
    ladderParams[0] = ladderFreq->get();
    ladderParams[1] = ladderRes->get();
    ladderParams[2] = ladderDrive->get();

    //Set Phaser for LFO
    phaserParams[0] = phaserRate->get();
    phaserParams[1] = phaserDepth->get();
    phaserParams[2] = phaserCenterFreq->get();
    phaserParams[3] = phaserFeedback->get();
    phaserParams[4] = phaserMix->get();

    //Set comb for LFO
    combParams[0] = combFreq->get();
    combParams[1] = combFeedback->get();
    combParams[2] = combGain->get();
    combParams[3] = combMix->get();
}

void SimpleSynthAudioProcessor::setLFOs(juce::AudioBuffer<float>& buffer)
{
    //LFO 1
    lfo1.setWaveType(setLFO1Wave);
    lfo1.setRate(lfo1Rate->get());
    lfo1Output = lfo1.processNextBlock(buffer); 
    lfo1.modulateADSR(lfo1attack1->get(), lfo1decay1->get(), lfo1sustain1->get(), lfo1release1->get(), lfo1oscGain1->get(), lfo1Output, osc1Params);
    lfo1.modulateADSR(lfo1attack2->get(), lfo1decay2->get(), lfo1sustain2->get(), lfo1release2->get(), lfo1oscGain2->get(), lfo1Output, osc2Params);
    lfo1.modulateLadderFilter(lfo1ladderFreq->get(), lfo1ladderRes->get(), lfo1ladderDrive->get(), lfo1Output, ladderParams);
    lfo1.modulatePhaserFilter(lfo1phaserRate->get(), lfo1phaserDepth->get(), lfo1phaserCenterFreq->get(), lfo1phaserDepth->get(), lfo1phaserMix->get(), lfo1Output, phaserParams);
    lfo1.modulateCombFilter(lfo1combFreq->get(), lfo1combFeedback->get(), lfo1combGain->get(), lfo1combMix->get(), lfo1Output, combParams);
   
    //LFO 2
    lfo2.setWaveType(setLFO2Wave);
    lfo2.setRate(lfo2Rate->get());
    lfo2Output = lfo2.processNextBlock(buffer);
    lfo2.modulateADSR(lfo2attack1->get(), lfo2decay1->get(), lfo2sustain1->get(), lfo2release1->get(), lfo2oscGain1->get(), lfo2Output, osc1Params);
    lfo2.modulateADSR(lfo2attack2->get(), lfo2decay2->get(), lfo2sustain2->get(), lfo2release2->get(), lfo2oscGain2->get(), lfo2Output, osc2Params);
    lfo2.modulateLadderFilter(lfo2ladderFreq->get(), lfo2ladderRes->get(), lfo2ladderDrive->get(), lfo2Output, ladderParams);
    lfo2.modulatePhaserFilter(lfo2phaserRate->get(), lfo2phaserDepth->get(), lfo2phaserCenterFreq->get(), lfo2phaserDepth->get(), lfo2phaserMix->get(), lfo2Output, phaserParams);
    lfo2.modulateCombFilter(lfo2combFreq->get(), lfo2combFeedback->get(), lfo2combGain->get(), lfo2combMix->get(), lfo2Output, combParams);
}

float SimpleSynthAudioProcessor::getOutRMS(int channel)
{
    jassert(channel == 0 || channel == 1);
    return rmsOut[channel];
}

juce::AudioProcessorValueTreeState::ParameterLayout SimpleSynthAudioProcessor::createParameterLayout()
{
    using namespace juce;
    AudioProcessorValueTreeState::ParameterLayout layout;

    auto range = NormalisableRange<float>(0, 5, .001, .7);
    auto zeroToOne = NormalisableRange<float>(0, 1, .01, 1);
    auto gainRange = NormalisableRange<float>(-60, 6, .1, 1);
    auto outGainRange = NormalisableRange<float>(-24, 24, .1, 1);
    auto fmRange = NormalisableRange<float>(0, 1000, 1, 1);
    auto freqRange = NormalisableRange<float>(20, 20000, 1, 1);
    auto driveRange = NormalisableRange<float>(1, 10, .1, 1);
    auto feedbackRange = NormalisableRange<float>(-1, 1, .01, 1);
    auto lfoRange = NormalisableRange<float>(.1, 10, .1, 1);
    auto combRange = NormalisableRange<float>(1, 75, .1, 1);
    auto combFeedbackRange = NormalisableRange<float>(.3, .75, .01, 1);

    auto filterTypes = juce::StringArray{ "ladder", "phaser", "comb"};
    auto ladderFilterTypes = juce::StringArray{ "LP12", "HP12", "BP12", "LP24", "HP24", "BP24" };

    layout.add(std::make_unique<AudioParameterFloat>("gGain", "Global Gain", outGainRange, 0));
    layout.add(std::make_unique<AudioParameterBool>("bypassSynth1", "Synth 1 Bypass", false));
    layout.add(std::make_unique<AudioParameterBool>("bypassSynth2", "Synth 2 Bypass", false));
    layout.add(std::make_unique<AudioParameterBool>("bypassFilter", "Filter Bypass", false));

    //layout.add(std::make_unique<AudioParameterInt>("voices", "Synth Voices", 1, 8, 1));

    //osc 1 
    layout.add(std::make_unique<AudioParameterBool>("sine1", "Osc 1 Sine Wave", true));
    layout.add(std::make_unique<AudioParameterBool>("saw1", "Osc 1 Saw Wave", false));
    layout.add(std::make_unique<AudioParameterBool>("square1", "Osc 1 Square Wave", false));
    layout.add(std::make_unique<AudioParameterBool>("triangle1", "Osc 1 Triangle Wave", false));

    layout.add(std::make_unique<AudioParameterFloat>("attack1", "Osc 1 Attack", range, .5f));
    layout.add(std::make_unique<AudioParameterFloat>("decay1", "Osc 1 Decay", range, .05));
    layout.add(std::make_unique<AudioParameterFloat>("sustain1", "Osc 1 Sustain", zeroToOne, 1));
    layout.add(std::make_unique<AudioParameterFloat>("release1", "Osc 1 Release", range, .5));
    layout.add(std::make_unique<AudioParameterFloat>("oscGain1", "Osc 1 Gain", gainRange, -6));

    //osc 2
    layout.add(std::make_unique<AudioParameterBool>("sine2", "Osc 2 Sine Wave", true));
    layout.add(std::make_unique<AudioParameterBool>("saw2", "Osc 2 Saw Wave", false));
    layout.add(std::make_unique<AudioParameterBool>("square2", "Osc 2 Square Wave", false));
    layout.add(std::make_unique<AudioParameterBool>("triangle2", "Osc 2 Triangle Wave", false));

    layout.add(std::make_unique<AudioParameterFloat>("attack2", "Osc 2 Attack", range, .05));
    layout.add(std::make_unique<AudioParameterFloat>("decay2", "Osc 2 Decay", range, .05));
    layout.add(std::make_unique<AudioParameterFloat>("sustain2", "Osc 2 Sustain", zeroToOne, .5));
    layout.add(std::make_unique<AudioParameterFloat>("release2", "Osc 2 Release", range, .5));
    layout.add(std::make_unique<AudioParameterFloat>("oscGain2", "Osc 2 Gain", gainRange, -6));

    layout.add(std::make_unique<AudioParameterBool>("fmOsc", "FM from Osc 2", false));
    layout.add(std::make_unique<AudioParameterFloat>("fmDepth", "FM Depth", fmRange, 0));

    //Filter
    //Select Filter
    layout.add(std::make_unique<AudioParameterChoice>("filterType", "Filter Type", filterTypes, 0));

    //Ladder
    layout.add(std::make_unique<AudioParameterChoice>("ladderChoice", "Ladder Filter Types", ladderFilterTypes, 0));
    layout.add(std::make_unique<AudioParameterFloat>("ladderFreq", "Ladder Frequency", freqRange, 100));
    layout.add(std::make_unique<AudioParameterFloat>("ladderRes", "Ladder Resonance", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("ladderDrive", "Ladder Drive", driveRange, 1));

    //comb
    layout.add(std::make_unique<AudioParameterFloat>("combFreq", "Comb Filter Frequency", combRange, 20));
    layout.add(std::make_unique<AudioParameterFloat>("combFeedback", "Comb Filter Feedback", combFeedbackRange, .3));
    layout.add(std::make_unique<AudioParameterFloat>("combGain", "Comb Filter Gain", range, 1));
    layout.add(std::make_unique<AudioParameterFloat>("combMix", "Comb Filter Mix", zeroToOne, 0));

    //Phaser
    layout.add(std::make_unique<AudioParameterFloat>("phaserRate", "Phaser Rate", lfoRange, 0.1));
    layout.add(std::make_unique<AudioParameterFloat>("phaserDepth", "Phaser Depth", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("phaserCenterFreq", "Phaser Center Frequency", freqRange, 20));
    layout.add(std::make_unique<AudioParameterFloat>("phaserFeedback", "Phaser Feedback", feedbackRange, 0));
    layout.add(std::make_unique<AudioParameterFloat>("phaserMix", "Phaser Mix", zeroToOne, 0));

    //LFO1 wavetype
    layout.add(std::make_unique<AudioParameterBool>("lfo1sine", "LFO 1 Sine Wave", true));
    layout.add(std::make_unique<AudioParameterBool>("lfo1saw", "LFO 1 Saw Wave", false));
    layout.add(std::make_unique<AudioParameterBool>("lfo1square", "LFO 1 Square Wave", false));
    layout.add(std::make_unique<AudioParameterBool>("lfo1triangle", "LFO 1 Triangle Wave", false));

    //LFO1
    layout.add(std::make_unique<AudioParameterFloat>("lfo1attack1", "LFO1 Osc 1 Attack", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1decay1", "LFO1 Osc 1 Decay", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1sustain1", "LFO1 Osc 1 Sustain", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1release1", "LFO1 Osc 1 Release", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1oscGain1", "LFO1 Osc 1 Gain", zeroToOne, 0));

    layout.add(std::make_unique<AudioParameterFloat>("lfo1attack2", "LFO1 Osc 2 Attack", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1decay2", "LFO1 Osc 2 Decay", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1sustain2", "LFO1 Osc 2 Sustain", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1release2", "LFO1 Osc 2 Release", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1oscGain2", "LFO1 Osc 2 Gain", zeroToOne, 0));

    layout.add(std::make_unique<AudioParameterFloat>("lfo1ladderFreq", "LFO1 Ladder Cuttoff", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1ladderRes", "LFO1 Ladder Resonance", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1ladderDrive", "LFO1 Ladder Drive", zeroToOne, 0));

    layout.add(std::make_unique<AudioParameterFloat>("lfo1phaserRate", "LFO1 Phaser Rate", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1phaserDepth", "LFO1 Phaser Depth", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1phaserCenterFreq", "LFO1 Phaser Center Frequency", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1phaserFeedback", "LFO1 Phaser Feedback", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1phaserMix", "LFO1 Phaser Mix", zeroToOne, 0));

    layout.add(std::make_unique<AudioParameterFloat>("lfo1combFreq", "LFO1 Comb Frequency", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1combFeedback", "LFO1 Comb Feedback", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1combGain", "LFO1 Comb Gain", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo1combMix", "LFO1 Comb Mix", zeroToOne, 0));

    layout.add(std::make_unique<AudioParameterFloat>("lfo1Rate", "LFO1 Rate", lfoRange, 1));

    //LFO2 wavetype
    layout.add(std::make_unique<AudioParameterBool>("lfo2sine", "LFO 2 Sine Wave", true));
    layout.add(std::make_unique<AudioParameterBool>("lfo2saw", "LFO 2 Saw Wave", false));
    layout.add(std::make_unique<AudioParameterBool>("lfo2square", "LFO 2 Square Wave", false));
    layout.add(std::make_unique<AudioParameterBool>("lfo2triangle", "LFO 2 Triangle Wave", false));

    //LFO2
    layout.add(std::make_unique<AudioParameterFloat>("lfo2attack1", "LFO2 Osc 1 Attack", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2decay1", "LFO2 Osc 1 Decay", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2sustain1", "LFO2 Osc 1 Sustain", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2release1", "LFO2 Osc 1 Release", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2oscGain1", "LFO2 Osc 1 Gain", zeroToOne, 0));

    layout.add(std::make_unique<AudioParameterFloat>("lfo2attack2", "LFO2 Osc 2 Attack", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2decay2", "LFO2 Osc 2 Decay", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2sustain2", "LFO2 Osc 2 Sustain", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2release2", "LFO2 Osc 2 Release", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2oscGain2", "LFO2 Osc 2 Gain", zeroToOne, 0));

    layout.add(std::make_unique<AudioParameterFloat>("lfo2ladderFreq", "LFO2 Ladder Cuttoff", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2ladderRes", "LFO2 Ladder Resonance", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2ladderDrive", "LFO2 Ladder Drive", zeroToOne, 0));

    layout.add(std::make_unique<AudioParameterFloat>("lfo2phaserRate", "LFO2 Phaser Rate", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2phaserDepth", "LFO2 Phaser Depth", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2phaserCenterFreq", "LFO2 Phaser Center Frequency", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2phaserFeedback", "LFO2 Phaser Feedback", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2phaserMix", "LFO2 Phaser Mix", zeroToOne, 0));

    layout.add(std::make_unique<AudioParameterFloat>("lfo2combFreq", "LFO2 Comb Frequency", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2combFeedback", "LFO2 Comb Feedback", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2combGain", "LFO2 Comb Gain", zeroToOne, 0));
    layout.add(std::make_unique<AudioParameterFloat>("lfo2combMix", "LFO2 Comb Mix", zeroToOne, 0));

    layout.add(std::make_unique<AudioParameterFloat>("lfo2Rate", "LFO2 Rate", lfoRange, 1));

    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleSynthAudioProcessor();
}
