#include "PluginEditor.h"
GuuVerbEditor::GuuVerbEditor(GuuVerbAudioProcessor& proc): AudioProcessorEditor(proc), p(proc){ setSize(500,350); }
void GuuVerbEditor::paint(juce::Graphics& g){
    g.fillAll(juce::Colour(0xff6a00ff));
    g.setColour(juce::Colours::white);
    g.setFont(28.f); g.drawText("Guu'Verb - ULTRA LONG",0,20,getWidth(),40,juce::Justification::centred);
    g.setFont(14.f); g.drawText("Size / Damp / Mix in host",0,260,getWidth(),20,juce::Justification::centred);
}
void GuuVerbEditor::resized(){}
juce::AudioProcessorEditor* GuuVerbAudioProcessor::createEditor(){ return new GuuVerbEditor(*this); }
