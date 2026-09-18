#include "PluginProcessor.h"
#include "PluginEditor.h"
GuuVerbAudioProcessor::GuuVerbAudioProcessor(): AudioProcessor(BusesProperties().withInput("Input",juce::AudioChannelSet::stereo()).withOutput("Output",juce::AudioChannelSet::stereo())), apvts(*this,nullptr,"Params",createParams()){}
juce::AudioProcessorValueTreeState::ParameterLayout GuuVerbAudioProcessor::createParams(){
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> p;
    p.push_back(std::make_unique<juce::AudioParameterFloat>("size","Size",0.0f,1.0f,0.9f));
    p.push_back(std::make_unique<juce::AudioParameterFloat>("damp","Damp",0.0f,1.0f,0.4f));
    p.push_back(std::make_unique<juce::AudioParameterFloat>("mix","Mix",0.0f,1.0f,0.5f));
    return {p.begin(),p.end()};
}
void GuuVerbAudioProcessor::prepareToPlay(double sr,int b){reverb.prepare(sr,b);}
void GuuVerbAudioProcessor::processBlock(juce::AudioBuffer<float>& buf,juce::MidiBuffer&){
    juce::ScopedNoDenormals nd;
    reverb.setSize(apvts.getRawParameterValue("size")->load());
    reverb.setDamping(apvts.getRawParameterValue("damp")->load());
    reverb.process(buf);
}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(){return new GuuVerbAudioProcessor();}
