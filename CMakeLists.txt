cmake_minimum_required(VERSION 3.22)
project(GuuVerb VERSION 1.0.0)

include(FetchContent)
FetchContent_Declare(JUCE GIT_REPOSITORY https://github.com/juce-framework/JUCE.git GIT_TAG 8.0.6)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(GuuVerb
    COMPANY_NAME "GuuAudio"
    PRODUCT_NAME "Guu'Verb"
    PLUGIN_MANUFACTURER_CODE GuuA
    PLUGIN_CODE GuuV
    FORMATS VST3
    IS_SYNTH FALSE
)

juce_generate_juce_header(GuuVerb)

target_sources(GuuVerb PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
)

target_link_libraries(GuuVerb PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
)
