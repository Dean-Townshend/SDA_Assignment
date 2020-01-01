#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent (Audio& a) :   audio (a), thumbnailCache(5),
thumbnailComp(512, formatManager, thumbnailCache),
positionOverlay(transportSource)
{
	for (int i = 0; i < Audio::NumberOfFilePlayers; i++)
	{
		filePlayerGui[i].setFilePlayer(audio.getFilePlayer(i));
		addAndMakeVisible(filePlayerGui[i]);
	}	

	addAndMakeVisible(&thumbnailComp);
	addAndMakeVisible(&positionOverlay);
    
    setSize (600, 600);
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
	Rectangle<int> controlArea = area.removeFromRight(area.getWidth());

	Rectangle<int> waveformThumb = controlArea.removeFromTop(controlArea.getHeight() / 2);

	thumbnailComp.setBounds(waveformThumb);
	positionOverlay.setBounds(waveformThumb);

	int heightPerEl = area.getHeight() / NumElements;

	std::array<Rectangle<int>, Audio::NumberOfFilePlayers> guiComp;

	for (int i = 0; i < Audio::NumberOfFilePlayers; i++)
	{
		guiComp[i] = padArea.removeFromTop(heightPerEl);
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
                                           &audioSettingsComp, this, Colours::lightgrey, true);
        }
    }
}
