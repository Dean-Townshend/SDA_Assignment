#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../audio/Audio.h"
#include "SamplePlayerGui.h"
#include "WaveformGui.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component,
                        public MenuBarModel,
						private Slider::Listener,
						private Button::Listener
{
public:

	std::array<String, 9 > notes = { "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5", "\0" };
	
    //==============================================================================

    /** Constructor */
	MainComponent(Audio& a);

    /** Destructor */
    ~MainComponent();

    void resized() override;
    
    //MenuBarEnums/Callbacks========================================================
    enum Menus
    {
        FileMenu = 0,
        
        NumMenus
    };
    
    enum FileMenuItems
    {
        AudioPrefs = 1,
        
        NumFileItems
    };
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;

    
private:

	//Slider Listener
	void sliderValueChanged(Slider* slider) override;

	//Button Listener
	void buttonClicked(Button* button) override;

	int playerInView = 0;

    Audio& audio;
    
	std::array <SamplePlayerGui, Audio::NumOfFilePlayers> filePlayerGui;

	Slider verbSlider;
	Label verbSliderLabel;

	Slider levelSlider;
	Label levelSliderLabel;

	std::array <TextButton, 8> padButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
