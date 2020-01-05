#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent (Audio& a) : audio (a)
{
	for (int i = 0; i < Audio::NumOfFilePlayers; i++)
	{
		filePlayerGui[i].setFilePlayer(audio.getFilePlayer(i));
		addAndMakeVisible(filePlayerGui[i]);
	}	
    
    setSize (600, 750);
}

MainComponent::~MainComponent()
{
    
}

//==============================================================================
void MainComponent::resized()
{
	Rectangle<int> area = getLocalBounds();
	Rectangle<int> GuiArea = area.removeFromLeft(area.getWidth());

	const int NumElements = Audio::NumOfFilePlayers;
	int heightPerEl = area.getHeight() / NumElements;

	std::array<Rectangle<int>, Audio::NumOfFilePlayers> guiComp;

	for (int i = 0; i < Audio::NumOfFilePlayers; i++)
	{
		guiComp[i] = GuiArea.removeFromTop(heightPerEl);
		filePlayerGui[i].setBounds(guiComp[i]);
	}	
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
                                           &audioSettingsComp, this, Colours::dimgrey, true);
        }
    }
}
