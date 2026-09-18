cmake_minimum_required(VERSION 3.22)
project(GuuVerb VERSION 1.0.0)
add_subdirectory(JUCE)
juce_add_plugin(GuuVerb
    COMPANY_NAME "Guu"
    PLUGIN_MANUFACTURER_CODE GuuA
    PLUGIN_CODE GuuV
    FORMATS VST3
    PRODUCT_NAME "GuuVerb"
    COPY_PLUGIN_AFTER_BUILD FALSE
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
