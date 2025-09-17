#include "MainComponent.h"
#include <random>


MainComponent::MainComponent()
{
    populateMidiOutputs();           //populate dropdown w outputs

    addAndMakeVisible(midiOutputSelector);
    addAndMakeVisible(sendNoteButton); 

    sendNoteButton.addListener(this);        //called to listen for button clicks

    setSize(600, 400);
}


MainComponent::~MainComponent()
{
    sendNoteButton.removeListener(this);          //"destructor" - listener has to be removed along with button because otherwise it becomes "orphaned"
}


//coloring
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setFont (juce::FontOptions (18.0f));
    g.setColour (juce::Colours::white);
}


//formatting
void MainComponent::resized()
{
    juce::FlexBox fb;

    fb.flexDirection = juce::FlexBox::Direction::column;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent   = juce::FlexBox::AlignContent::stretch; // stretch horizontally

    fb.items.add(juce::FlexItem(midiOutputSelector).withMinHeight(30.0f).withMargin(10.0f).withFlex(1));
    fb.items.add(juce::FlexItem(sendNoteButton).withMinHeight(30.0f).withMargin(10.0f).withFlex(1));

    fb.performLayout(getLocalBounds().toFloat());
}




//dropdown for midi outputs
void MainComponent::populateMidiOutputs()
{
    //get list of all MIDI output devices on system
    auto midiDevices = juce::MidiOutput::getAvailableDevices();

    midiOutputSelector.clear();             //clear existing

    for (int i = 0; i < midiDevices.size(); i++)
        midiOutputSelector.addItem(midiDevices[i].name, i + 1);               //add each MIDI output device to dropdown

    //when user selects MIDI device
    midiOutputSelector.onChange = [this, midiDevices]()
    {
        //get & check index of selected device
        auto idx = midiOutputSelector.getSelectedId() - 1;

        if (idx >= 0 && idx < midiDevices.size())
        {
            midiOutput = juce::MidiOutput::openDevice(midiDevices[idx].identifier);            //open selected MIDI output
        }
    };
}


//button actions
void MainComponent::buttonClicked(juce::Button* button)
{

    if (button == &sendNoteButton && midiOutput)
    {
        //random MIDI note between 60-72 (I did one octave from C4 (mid C) to C5)
        int note = rand() % 60 + 12;

        //send MIDI note-on msg
        juce::MidiMessage msgOn = juce::MidiMessage::noteOn(1, note, (juce::uint8)100);
        midiOutput->sendMessageNow(msgOn);

        //send MIDI note-off msg
        juce::MidiMessage msgOff = juce::MidiMessage::noteOff(1, note, (juce::uint8)0);
        midiOutput->sendMessageNow(msgOff);
    }
}
