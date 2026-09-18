#pragma once
#include <juce_dsp/juce_dsp.h>
#include <array>
#include <random>

class FDNReverb {
public:
    void prepare(double sr, int maxBlock){
        sampleRate = sr;
        for(auto& d: delays) d.prepare({sr, (juce::uint32)maxBlock, 1});
        for(auto& f: filters) f.prepare({sr, (juce::uint32)maxBlock, 1});
        setSize(0.95f); setDamping(0.4f);
        std::mt19937 rng(42);
        std::uniform_real_distribution<float> dist(0.02f, 0.08f);
        for(int i=0;i<8;i++) delays[i].setDelay((dist(rng)+i*0.015f)*sampleRate);
    }
    void setSize(float s){ for(auto& d: delays) d.setFeedback(s*0.99f); }
    void setDamping(float dmp){
        for(auto& f: filters){ f.setType(juce::dsp::StateVariableTPTFilterType::lowpass); f.setCutoffFrequency(20000.0f * (1.0f - dmp*0.9f)); }
    }
    void process(juce::AudioBuffer<float>& buf){
        for(int ch=0; ch<buf.getNumChannels(); ++ch){
            auto* data = buf.getWritePointer(ch);
            for(int s=0; s<buf.getNumSamples(); ++s){
                float in = data[s];
                float out = 0;
                for(int i=0;i<8;i++){ float dl = delays[i].popSample(0); dl = filters[i].processSample(0, dl); out+=dl; delays[i].pushSample(0, in + dl*0.7f); }
                data[s] = out*0.12f + in*0.3f;
            }
        }
    }
private:
    double sampleRate=48000;
    std::array<juce::dsp::DelayLine<float>,8> delays;
    std::array<juce::dsp::StateVariableTPTFilter<float>,8> filters;
};
