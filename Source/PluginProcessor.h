#pragma once
#include <JuceHeader.h>
#include "FDNReverb.h"

class GuuVerbAudioProcessor : public juce::AudioProcessor {
public:
    GuuVerbAudioProcessor();
    void prepareToPlay(double sr, int bs) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported(const BusesLayout& l) const override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return "GuuVerb"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 20.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}
    void getStateInformation(juce::MemoryBlock&) override;
    void setStateInformation(const void*, int) override;
    static juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    juce::AudioProcessorValueTreeState apvts;
private:
    MyFDNReverb reverb;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuuVerbAudioProcessor)
};
