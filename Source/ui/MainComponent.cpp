#include "MainComponent.h"

MainComponent::MainComponent (Audio& a) : audio (a)
{
	for (int i = 0; i < Audio::NumOfFilePlayers; i++)
	{
		PadControlsGui[i].setFilePlayer(audio.getFilePlayer(i));
	}	
  
	//Reverb slider
	verbSlider.addListener(this);
	addAndMakeVisible(verbSlider);
	verbSlider.setSliderStyle(Slider::LinearHorizontal);
	verbSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	verbSlider.setRange(0.0, 1.0);
	verbSlider.setValue(0.0);
	verbSlider.setTextValueSuffix(" *");
	verbSlider.setNumDecimalPlacesToDisplay(3);
	//Verb Label
	addAndMakeVisible(verbSliderLabel);
	verbSliderLabel.setText("Reverb:", dontSendNotification);
	//startPosSliderLabel.attachToComponent(&startPosSlider, true);
	verbSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);
	
	//Level slider
	levelSlider.addListener(this);
	addAndMakeVisible(levelSlider);
	levelSlider.setSliderStyle(Slider::LinearHorizontal);
	levelSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	levelSlider.setRange(0.0, 1.0);
	levelSlider.setValue(0.0);
	levelSlider.setTextValueSuffix(" *");
	levelSlider.setNumDecimalPlacesToDisplay(3);
	levelSlider.setValue(0.5);
	//Level slider label
	levelSliderLabel.setText("Volume:", dontSendNotification);
	//startPosSliderLabel.attachToComponent(&startPosSlider, true);
	levelSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);
	addAndMakeVisible(levelSliderLabel);

	//Pad Grid
	for (int i = 0; i < 8; i++)
	{
		padButton[i].addListener(this);
		addAndMakeVisible(padButton[i]);
		padButton[i].setButtonText(notes[i]);
	}

	//Set the name labels of each sample player
	for (int i = 0; i < Audio::NumOfFilePlayers; i++)
	{
		PadControlsGui[i].setNameLabelText(notes[i]);
	}

    setSize (600, 600);
}

MainComponent::~MainComponent()
{
    
}

void MainComponent::resized()
{
	Rectangle<int> area = getLocalBounds();
	Rectangle<int> guiArea = area;

	//Pad controls layout
	Rectangle<int> padControlGuiArea = guiArea.removeFromRight(area.getWidth() * 0.5);
	PadControlsGui[playerInView].setBounds(padControlGuiArea);
	addAndMakeVisible(PadControlsGui[playerInView]);

	//Pad grid layout
	Rectangle<int> padGuiArea = guiArea.removeFromTop(guiArea.getHeight()*0.8);

	int heightPerRow = padGuiArea.getHeight()/4;
	int widthPerRow = padGuiArea.getWidth()/2;

	std::array < Rectangle<int>, 4> padRows;
	std::array < Rectangle<int>, 8> padButts;

	//Remove a section for each row
	for (int i = 0; i < 4; i++)
	{
		padRows[i] = padGuiArea.removeFromTop(heightPerRow);
	}

	//Remove a section of each row for pads
	for (int b = 0; b < 2; b++)
	{
		padButts[b] = padRows[0].removeFromLeft(widthPerRow);
	}
	for (int b = 2; b < 4; b++)
	{
		padButts[b] = padRows[1].removeFromLeft(widthPerRow);
	}
	for (int b = 4; b < 6; b++)
	{
		padButts[b] = padRows[2].removeFromLeft(widthPerRow);
	}
	for (int b = 6; b < 8; b++)
	{
		padButts[b] = padRows[3].removeFromLeft(widthPerRow);
	}
	for (int i = 0; i < 8; i++)
	{
		padButton[i].setBounds(padButts[i]);
	}

	//Master controls
	Rectangle<int> masterControls = guiArea;

	Rectangle<int> reverb = masterControls.removeFromTop(masterControls.getHeight() / 2);
	Rectangle<int> reverbSlider = reverb.removeFromRight(reverb.getWidth() * 0.7);
	Rectangle<int> reverbLabel = reverb;

	verbSlider.setBounds(reverbSlider);
	verbSliderLabel.setBounds(reverbLabel);

	Rectangle<int> level = masterControls;
	Rectangle<int> levelSliderArea = level.removeFromRight(level.getWidth() * 0.7);
	Rectangle<int> levelLabel = level;

	levelSlider.setBounds(levelSliderArea);
	levelSliderLabel.setBounds(levelLabel);
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


void MainComponent::buttonClicked(Button* button)
{
	removeChildComponent(&PadControlsGui[playerInView]); //Remove the previous pad controls shown 

	if (button == &padButton[0])
	{
		DBG("C4");
		playerInView = 0;
	}
	if (button == &padButton[1])
	{
		DBG("D4");
		playerInView = 1;
	}
	if (button == &padButton[2])
	{
		DBG("E4");
		playerInView = 2;
	}
	if (button == &padButton[3])
	{
		DBG("F4");
		playerInView = 3;
	}
	if (button == &padButton[4])
	{
		DBG("G4");
		playerInView = 4;
	}
	if (button == &padButton[5])
	{
		DBG("A4");
		playerInView = 5;
	}
	if (button == &padButton[6])
	{
		DBG("B4");
		playerInView = 6;
	}
	if (button == &padButton[7])
	{
		DBG("C5");
		playerInView = 7;
	}

	resized(); //Redraws screen to show controls for updated selected pad
}

void MainComponent::sliderValueChanged(Slider* slider)
{
	if (slider == &verbSlider)
	{
		audio.setReverbParam(verbSlider.getValue(), 0.5);
	}
	if (slider == &levelSlider)
	{
		audio.setLevel(levelSlider.getValue());
	}
}
