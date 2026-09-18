#pragma once
#include "PluginProcessor.h"

class GuuVerbEditor : public juce::AudioProcessorEditor {
public:
    explicit GuuVerbEditor(GuuVerbAudioProcessor&);
    ~GuuVerbEditor() override = default;
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    GuuVerbAudioProcessor& proc;
    
    juce::Slider sizeSlider, dampSlider, mixSlider;
    juce::Label sizeLabel, dampLabel, mixLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sizeAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuuVerbEditor)
};
