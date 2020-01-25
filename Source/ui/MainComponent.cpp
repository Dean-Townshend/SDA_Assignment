#include "MainComponent.h"

MainComponent::MainComponent (Audio& a) : audio (a)
{
	for (int i = 0; i < Audio::NumOfFilePlayers; i++)
	{
		filePlayerGui[i].setFilePlayer(audio.getFilePlayer(i));
	}	
  
	addAndMakeVisible(filePlayerGui[0]);

	verbSlider.addListener(this);
	addAndMakeVisible(verbSlider);
	verbSlider.setSliderStyle(Slider::LinearHorizontal);
	verbSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	verbSlider.setRange(0.1, 5.0);
	verbSlider.setValue(0.1);
	verbSlider.setTextValueSuffix(" *");
	verbSlider.setNumDecimalPlacesToDisplay(3);

	//Labels
	verbSliderLabel.setText("Reverb:", dontSendNotification);
	//startPosSliderLabel.attachToComponent(&startPosSlider, true);
	verbSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);
	addAndMakeVisible(verbSliderLabel);

	levelSlider.addListener(this);
	addAndMakeVisible(levelSlider);
	levelSlider.setSliderStyle(Slider::LinearHorizontal);
	levelSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	levelSlider.setRange(0.1, 5.0);
	levelSlider.setValue(0.1);
	levelSlider.setTextValueSuffix(" *");
	levelSlider.setNumDecimalPlacesToDisplay(3);

	//Labels
	levelSliderLabel.setText("Volume:", dontSendNotification);
	//startPosSliderLabel.attachToComponent(&startPosSlider, true);
	levelSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);
	addAndMakeVisible(levelSliderLabel);

	for (int i = 0; i < 8; i++)
	{
		addAndMakeVisible(pads[i]);
		pads[i].setButtonText(notes[i]);
	}

    setSize (600, 600);
}

MainComponent::~MainComponent()
{
    
}

//==============================================================================
void MainComponent::resized()
{
	Rectangle<int> area = getLocalBounds();
	Rectangle<int> guiArea = area;
	Rectangle<int> controlGuiArea = guiArea.removeFromRight(area.getWidth() * 0.5);

	filePlayerGui[0].setBounds(controlGuiArea);

	
	Rectangle<int> padGuiArea = guiArea.removeFromTop(guiArea.getHeight()*0.8);


	int heightPerRow = padGuiArea.getHeight()/4;
	int widthPerRow = padGuiArea.getWidth()/2;

	std::array < Rectangle<int>, 4> padRows;
	std::array < Rectangle<int>, 8> padButts;


	for (int i = 0; i < 4; i++)
	{
		padRows[i] = padGuiArea.removeFromTop(heightPerRow);
	}
	
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
			pads[i].setBounds(padButts[i]);

		}


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

void MainComponent::sliderValueChanged(Slider* slider)
{
	if (slider == &verbSlider)
	{
		//DBG(verbSlider.getValue());
	}

}
