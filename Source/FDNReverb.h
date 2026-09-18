#pragma once
#include <JuceHeader.h>
class MyFDNReverb {
public:
    void prepare(double sr,int maxBlock){
        for(auto& d: delays) d.prepare({sr,(juce::uint32)maxBlock,(juce::uint32)(sr*4)});
    }
    void setSize(float s){ size = juce::jlimit(0.0f,1.0f,s); }
    void setDamping(float d){ damp = juce::jlimit(0.0f,1.0f,d); }
    void process(juce::AudioBuffer<float>& buf){
        auto* l = buf.getWritePointer(0);
        auto* r = buf.getNumChannels()>1? buf.getWritePointer(1):nullptr;
        for(int i=0;i<buf.getNumSamples();++i){
            float inL = l[i];
            float inR = r? r[i]:inL;
            float outL=0,outR=0;
            for(int j=0;j<8;++j){
                float dly = delays[j].popSample(0);
                float fb = dly * (0.68f + size*0.30f) * (1.0f - damp*0.3f);
                if(j%2==0) delays[j].pushSample(0, inL*0.12f + fb);
                else delays[j].pushSample(0, inR*0.12f + fb);
                outL += dly * (j<4?0.28f:0.05f);
                outR += dly * (j>=4?0.28f:0.05f);
            }
            l[i] = l[i]*0.5f + outL*0.6f;
            if(r) r[i] = r[i]*0.5f + outR*0.6f;
        }
    }
private:
    float size=0.92f,damp=0.35f;
    std::array<juce::dsp::DelayLine<float,juce::dsp::DelayLineInterpolationTypes::Linear>,8> delays;
};
