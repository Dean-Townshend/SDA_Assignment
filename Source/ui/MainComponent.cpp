#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent (Audio& a) :   audio (a)
{
	for (int i = 0; i < Audio::NumberOfFilePlayers; i++)
	{
		filePlayerGui[i].setFilePlayer(audio.getFilePlayer(i));
		addAndMakeVisible(filePlayerGui[i]);
	}	
    
    setSize (400, 400);
}

MainComponent::~MainComponent()
{
    
}

//==============================================================================
void MainComponent::resized()
{
	const int NumElements = Audio:: NumberOfFilePlayers; //How many elements need to be mapped out 

	Rectangle<int> area = getLocalBounds(); //Rectangle is used to map out each element of the file player
	Rectangle<int> padArea = area.removeFromLeft(area.getWidth()/2);
	
	int heightPerEl = area.getHeight() / NumElements;

	std::array<Rectangle<int>, Audio::NumberOfFilePlayers> guiComp;

	for (int i = 0; i < Audio::NumberOfFilePlayers; i++)
	{
		guiComp[i] = padArea.removeFromTop(heightPerEl);
		filePlayerGui[i].setBounds(guiComp[i]);
	}
	

	/*Rectangle<int> gui1 = area.removeFromTop(heightPerEl);
	Rectangle<int> gui2 = area.removeFromTop(heightPerEl);
	Rectangle<int> gui3 = area.removeFromTop(heightPerEl);
	Rectangle<int> gui4 = area.removeFromTop(heightPerEl);

	filePlayerGui[0].setBounds(gui1);
	filePlayerGui[1].setBounds(gui2);
	filePlayerGui[2].setBounds(gui3);
	filePlayerGui[3].setBounds(gui4);*/
	
}

//MenuBarCallbacks==============================================================
StringArray MainComponent::getMenuBarNames()
{
    const char* const names[] = { "File", 0 };
    return StringArray (names);
}

PopupMenu MainComponent::getMenuForIndex (int topLevelMenuIndex, const String& menuName)
{
    PopupMenu menu;
    if (topLevelMenuIndex == 0)
        menu.addItem(AudioPrefs, "Audio Prefrences", true, false);
    return menu;
}

void MainComponent::menuItemSelected (int menuItemID, int topLevelMenuIndex)
{
    if (topLevelMenuIndex == FileMenu)
    {
        if (menuItemID == AudioPrefs)
        {
            AudioDeviceSelectorComponent audioSettingsComp (audio.getAudioDeviceManager(),
                                                            2, 2, 2, 2, true, true, true, false);
            audioSettingsComp.setSize (450, 350);
            DialogWindow::showModalDialog ("Audio Settings",
                                           &audioSettingsComp, this, Colours::lightgrey, true);
        }
    }
}
