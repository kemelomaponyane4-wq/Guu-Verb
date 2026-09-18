#pragma once
#include <JuceHeader.h>

class MyFDNReverb {
public:
    MyFDNReverb() {}

    void prepare(double sr, int maxBlock) {
        sampleRate = sr;
        // prime numbers for ultra long tail - no ringing
        const int primes[16] = { 1557, 1637, 1811, 1933, 2113, 2273, 2477, 2647, 2777, 2971, 3217, 3413, 3631, 3817, 4003, 4201 };

        for (int i = 0; i < 16; ++i) {
            delays[i].prepare({sr, (juce::uint32)maxBlock, (juce::uint32)(sr * 5.0)});
            delays[i].setDelay((float)primes[i] * (0.9f + (float)i * 0.02f));
        }
        for (int i = 0; i < 4; ++i) {
            allpass[i].prepare({sr, (juce::uint32)maxBlock, (juce::uint32)(sr * 0.5)});
            allpass[i].setDelay( (i+1)* 89.0f );
        }
        dampFilter.prepare({sr, (juce::uint32)maxBlock, 2});
        dampFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        dampFilter.setCutoffFrequency(8000.0f);
    }

    void setSize(float s) { size = juce::jlimit(0.0f, 1.0f, s); }
    void setDamping(float d) {
        damp = juce::jlimit(0.0f, 1.0f, d);
        dampFilter.setCutoffFrequency(12000.0f - damp*9000.0f);
    }

    void process(juce::AudioBuffer<float>& buf) {
        const int numSamples = buf.getNumSamples();
        auto* left = buf.getWritePointer(0);
        auto* right = buf.getNumChannels() > 1? buf.getWritePointer(1) : nullptr;

        // hadamard mixing coeffs
        float fbGain = 0.68f + size * 0.30f; // 0.68 to 0.98 = infinite tail

        for (int n = 0; n < numSamples; ++n) {
            float inL = left[n];
            float inR = right? right[n] : inL;

            // input diffusion - 2x allpass
            for (int ap = 0; ap < 2; ++ap) {
                inL = allpass[ap].popSample(0, -0.6f * inL) + inL * 0.6f;
                inR = allpass[ap+2].popSample(0, -0.6f * inR) + inR * 0.6f;
                allpass[ap].pushSample(0, inL);
                allpass[ap+2].pushSample(0, inR);
            }

            float delayOut[16];
            for (int i = 0; i < 16; ++i) delayOut[i] = delays[i].popSample(0);

            // damp lowpass on feedback
            for (int i = 0; i < 16; ++i) {
                delayOut[i] = dampFilter.processSample(0, delayOut[i]);
            }

            // FDN matrix - householder mixing for density
            float mixed[16] = {0};
            for (int i = 0; i < 16; ++i) {
                for (int j = 0; j < 16; ++j) {
                    float coeff = (i == j)? 0.5f : -0.125f;
                    mixed[i] += delayOut[j] * coeff;
                }
            }

            float outL = 0, outR = 0;
            for (int i = 0; i < 16; ++i) {
                float toPush = (i % 2 == 0? inL : inR) * 0.08f + mixed[i] * fbGain;
                delays[i].pushSample(0, toPush);

                if (i < 8) outL += delayOut[i] * 0.18f;
                else outR += delayOut[i] * 0.18f;
            }

            left[n] = outL;
            if (right) right[n] = outR;
        }
    }

private:
    double sampleRate = 44100.0;
    float size = 0.92f;
    float damp = 0.35f;

    std::array<juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear>, 16> delays;
    std::array<juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear>, 4> allpass;
    juce::dsp::StateVariableTPTFilter<float> dampFilter;
};
