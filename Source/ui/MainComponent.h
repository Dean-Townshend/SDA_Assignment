#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../audio/Audio.h"
#include "FilePlayerGui.h"
#include "WaveformGui.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component,
                        public MenuBarModel
{
public:
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
    Audio& audio;
    
	std::array <FilePlayerGui, sizeof(Audio::NumberOfFilePlayers)> filePlayerGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
