#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../audio/Audio.h"
#include "SamplePlayerGui.h"
#include "WaveformGui.h"


/** Class responsible for placing all of the components in the window.
*/
class MainComponent   : public Component,
                        public MenuBarModel,
						private Slider::Listener,
						private Button::Listener
{
public:

	//This array is used to set the names of the button pads
	std::array<String, 16 > notes = { "C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5", "E6", "F6", "G6", "A6", "B7", "C8",  "\0" };

    /** Constructor */
	MainComponent(Audio& a);

    /** Destructor */
    ~MainComponent();

	/** Resizes the components the fit the window.
	*/
    void resized() override;
    
    //MenuBarEnums
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

	/** Overidden
	*/
    StringArray getMenuBarNames() override;

	/** Overidden
	*/
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    
	/** Overidden
	*/
	void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;

private:

	/** Overidden
	*/
	void sliderValueChanged(Slider* slider) override; //Slider Listener
	void buttonClicked(Button* button) override; //Button Listener

	int playerInView = 0;

    Audio& audio;
    
	std::array <FilePlayerGui, Audio::NumOfFilePlayers> PadControlsGui;

	//GUI components 
	Slider verbSizeSlider;
	Label verbSizeSliderLabel;
	Slider verbSlider;
	Label verbSliderLabel;
	Slider levelSlider;
	Label levelSliderLabel;
	std::array <TextButton, 8> padButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
