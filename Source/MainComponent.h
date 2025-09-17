#pragma once
#include <JuceHeader.h> 


class MainComponent : public juce::Component,
                      private juce::Button::Listener     //handles button click events
{
    public:

        MainComponent();                //constructor
        ~MainComponent() override;      //destructor

        void paint(juce::Graphics&) override;
        void resized() override;

    private:
        juce::ComboBox midiOutputSelector;                      //dropdown
        juce::TextButton sendNoteButton {"Send Random Note"};   //button
        std::unique_ptr<juce::MidiOutput> midiOutput;           //pointer; indicates current midi output

        void buttonClicked(juce::Button* button) override;     //callback for button action

        void populateMidiOutputs();                             //helper for dropdown (helps fill it in w the midi devices)

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)     //helps catch memory leaks
};
