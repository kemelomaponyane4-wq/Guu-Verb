#include "PluginEditor.h"
GuuVerbEditor::GuuVerbEditor(GuuVerbAudioProcessor& p): AudioProcessorEditor(p), proc(p){ setSize(520,360); }
void GuuVerbEditor::paint(juce::Graphics& g){
    g.fillAll(juce::Colour(0xff6a00ff));
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(32.0f,juce::Font::bold));
    g.drawText("Guu'Verb - ULTRA LONG",0,30,getWidth(),40,juce::Justification::centred);
    g.setFont(juce::Font(16.0f));
    g.drawText("Size / Damp / Mix - Automate in DAW",0,280,getWidth(),30,juce::Justification::centred);
    g.drawText("Tail > 10 sec - Purple Edition",0,305,getWidth(),20,juce::Justification::centred);
}
juce::AudioProcessorEditor* GuuVerbAudioProcessor::createEditor(){ return new GuuVerbEditor(*this); }
