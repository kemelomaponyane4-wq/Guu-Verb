#pragma once
#include "PluginProcessor.h"
class GuuVerbEditor : public juce::AudioProcessorEditor {
public:
    explicit GuuVerbEditor(GuuVerbAudioProcessor&);
    void paint(juce::Graphics&) override;
    void resized() override {}
private:
    GuuVerbAudioProcessor& proc;
};
