#include "MainComponent.h"


class DemoMIDIApp : public juce::JUCEApplication
{
    
    public:

        const juce::String getApplicationName() override       { return JUCE_APPLICATION_NAME_STRING; }
        const juce::String getApplicationVersion() override    { return JUCE_APPLICATION_VERSION_STRING; }
        bool moreThanOneInstanceAllowed() override             { return true; }

        //called when app starts
        void initialise(const juce::String& commandLine) override
        {
            juce::ignoreUnused (commandLine);

            //create window, title it the name of app
            mainWindow = std::make_unique<MainWindow>(getApplicationName());

        }

        void shutdown() override
        {
            mainWindow = nullptr; //deletes window
        }


    private:

        // main window
        class MainWindow : public juce::DocumentWindow
        {
    
        public:

            explicit MainWindow (juce::String name)
                : DocumentWindow (name,
                                juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                            .findColour (backgroundColourId),
                                allButtons)
            {
                setUsingNativeTitleBar(true);
                setContentOwned (new MainComponent(), true);

                #if JUCE_IOS || JUCE_ANDROID
                    setFullScreen (true);
                #else
                    setResizable (true, true);
                    centreWithSize (getWidth(), getHeight());
                #endif

                    setVisible (true);
            }

            void closeButtonPressed() override
            {
                getInstance()->systemRequestedQuit();
            }

        private:
            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
        };
    
    private:
        std::unique_ptr<MainWindow> mainWindow;
};

//generates main() that launches the app
START_JUCE_APPLICATION(DemoMIDIApp)
