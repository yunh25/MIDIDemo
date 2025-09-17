# CMake config for JUCE GUI app 

# compatibility check
cmake_minimum_required(VERSION 3.22)

# project def
project(MidiDemo VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)          # enforces c++ version
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JUCE_DIR "/Users/yunse/JUCE")

#if cloned
add_subdirectory(${JUCE_DIR} "JUCE_build")   #JUCE was cloned

#if installed..?
#set(JUCE_DIR "/Users/yunse/JUCE/build")  # pass -DJUCE_DIR=/path/to/JUCE/build to cmake
#find_package(JUCE CONFIG REQUIRED)

# gui app target
juce_add_gui_app(MidiDemo
    COMPANY_NAME "YunseoHa"
    PRODUCT_NAME "MIDIDemo"
    BUNDLE_ID "com.yunseoha.MidiDemo"
)

juce_generate_juce_header(MidiDemo)


# add source files to target
target_sources(MidiDemo
    PRIVATE
        Source/Main.cpp
        Source/MainComponent.cpp
)

# preprocessor defs to clean up unused modules
target_compile_definitions(MidiDemo
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:MidiDemo,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:MidiDemo,JUCE_VERSION>"
)


# link libraries & juce modules
target_link_libraries(MidiDemo
    PRIVATE
        juce::juce_gui_extra
        juce::juce_audio_devices  #necessary, in order to work w MIDI output devices
        juce::juce_audio_basics   #dependency of above module 
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
