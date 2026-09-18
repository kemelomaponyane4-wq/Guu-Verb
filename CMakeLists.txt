cmake_minimum_required(VERSION 3.15)
project(GuuVerb VERSION 1.0.0)
add_subdirectory(JUCE)
juce_add_plugin(GuuVerb
    COMPANY_NAME "GuuAudio"
    PRODUCT_NAME "Guu'Verb"
    PLUGIN_MANUFACTURER_CODE GuuA
    PLUGIN_CODE GuuV
    FORMATS VST3
    IS_SYNTH FALSE
)
target_sources(GuuVerb PRIVATE Source/PluginProcessor.cpp Source/PluginEditor.cpp)
target_link_libraries(GuuVerb PRIVATE juce::juce_audio_utils juce::juce_dsp)
