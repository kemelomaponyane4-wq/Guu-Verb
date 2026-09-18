#include "PluginProcessor.h"
#include "PluginEditor.h"
GuuVerbAudioProcessor::GuuVerbAudioProcessor(): AudioProcessor(BusesProperties().withInput("Input",juce::AudioChannelSet::stereo()).withOutput("Output",juce::AudioChannelSet::stereo())), apvts(*this,nullptr,"GuuParams",createParams()){}
juce::AudioProcessorValueTreeState::ParameterLayout GuuVerbAudioProcessor::createParams(){
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> p;
    p.push_back(std::make_unique<juce::AudioParameterFloat>("size","Size",0.0f,1.0f,0.92f));
    p.push_back(std::make_unique<juce::AudioParameterFloat>("damp","Damp",0.0f,1.0f,0.35f));
    p.push_back(std::make_unique<juce::AudioParameterFloat>("mix","Mix",0.0f,1.0f,0.5f));
    return {p.begin(),p.end()};
}
void GuuVerbAudioProcessor::prepareToPlay(double sr,int bs){ reverb.prepare(sr,bs); }
bool GuuVerbAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
void GuuVerbAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,juce::MidiBuffer&){
    juce::ScopedNoDenormals nd;
    reverb.setSize(apvts.getRawParameterValue("size")->load());
    reverb.setDamping(apvts.getRawParameterValue("damp")->load());
    reverb.process(buffer);
}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(){ return new GuuVerbAudioProcessor(); }
