/*
  ==============================================================================

    adsrData.cpp
    Created: 2 Aug 2023 2:31:49pm
    Author:  kylew

  ==============================================================================
*/

#include "oscData.h"
#include "../PluginProcessor.h"

oscData::oscData()
{

}

oscData::~oscData()
{

}

void oscData::setWaveType(std::array<bool, 4>& array)
{
    if (array[0])
        initialise([] (float x) { return std::sin(x); });
    else if(array[1])
        initialise([](float x) { return x / juce::MathConstants<float>::pi; });
    else if (array[2])
        initialise([](float x) { return x < 0.0f ? -1.f : 1.f; });
    else
        initialise([](float x) { return std::asin(std::cos(x)) / juce::MathConstants<float>::halfPi; });
}
