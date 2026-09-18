#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "FDNReverb.h"
class GuuVerbAudioProcessor : public juce::AudioProcessor {
public:
    GuuVerbAudioProcessor();
    void prepareToPlay(double sr,int spb) override;
    void processBlock(juce::AudioBuffer<float>&,juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override {return true;}
    const juce::String getName() const override {return "GuuVerb";}
    bool acceptsMidi() const override {return false;}
    bool producesMidi() const override {return false;}
    double getTailLengthSeconds() const override {return 8.0;}
    int getNumPrograms() override {return 1;} int getCurrentProgram() override {return 0;}
    void setCurrentProgram(int) override {} const juce::String getProgramName(int) override {return {};}
    void changeProgramName(int,const juce::String&) override {}
    void getStateInformation(juce::MemoryBlock&) override {}
    void setStateInformation(const void*,int) override {}
    void releaseResources() override {}
    juce::AudioProcessorValueTreeState apvts;
private:
    FDNReverb reverb;
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuuVerbAudioProcessor)
};
