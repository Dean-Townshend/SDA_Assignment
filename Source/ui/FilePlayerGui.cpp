#pragma once
#include "FilePlayerGui.h"
#include "WaveformGui.h"

FilePlayerGui::FilePlayerGui(): positionOverlay(), thumbnailCache(5),
thumbnailComp(512, formatManager, thumbnailCache)

{
	//Button
    playButton.addListener (this);
    addAndMakeVisible (playButton);
    
	//File Chooser
    formatManager.registerBasicFormats();
    fileChooser = std::make_unique<FilenameComponent> ("audiofile",
                                                       File(),
                                                       true, false, false,
                                                       formatManager.getWildcardForAllFormats(),
                                                       String(),
                                                       "(select an audio file)");
    fileChooser->addListener (this);
    addAndMakeVisible (fileChooser.get());

	//Start slider
	startPosSlider.addListener(this);
	addAndMakeVisible(startPosSlider);
	startPosSlider.setSliderStyle(Slider::LinearHorizontal);
	startPosSlider.setColour(Slider::thumbColourId, Colours::red);
	startPosSlider.setRange(0.0, 1.0);

	//Pitch slider
	pitchSlider.addListener(this);
	addAndMakeVisible(pitchSlider);
	pitchSlider.setSliderStyle(Slider::LinearHorizontal);
	pitchSlider.setColour(Slider::thumbColourId, Colours::blue);
	pitchSlider.setRange(0.1, 5.0);
	pitchSlider.setValue(0.1);

	//Waveform view
	addAndMakeVisible(&thumbnailComp);
	addAndMakeVisible(&positionOverlay);
}

FilePlayerGui::~FilePlayerGui()
{
    
}

void FilePlayerGui::paint(Graphics& g)
{

}

//Component
void FilePlayerGui::resized()
{
	Rectangle<int> area = getLocalBounds(); //Rectangle is used to map out each element of the file player

	const int NumElements = 4; //How many elements need to be mapped out 
	int heightPerEl = area.getHeight() / NumElements;

	Rectangle<int> controlArea = area.removeFromLeft(area.getWidth()/2);
	Rectangle<int> waveformArea = area;

	positionOverlay.setBounds(waveformArea);
	thumbnailComp.setBounds(waveformArea);
	
	Rectangle<int> playButtArea = controlArea.removeFromTop(heightPerEl);
	Rectangle<int> fileChooseArea = controlArea.removeFromTop(heightPerEl);
	Rectangle<int> startSliderArea = controlArea.removeFromBottom(heightPerEl);
	Rectangle<int> pitchSliderArea = controlArea.removeFromTop(heightPerEl);
	
	playButton.setBounds(playButtArea);
    fileChooser->setBounds (fileChooseArea);
	startPosSlider.setBounds(startSliderArea);
	pitchSlider.setBounds(pitchSliderArea);
}


//Button Listener
void FilePlayerGui::buttonClicked (Button* button)
{
    if (filePlayer != nullptr && button == &playButton)
    {
        filePlayer->setPlaying( ! filePlayer->isPlaying());
		filePlayer->setPosition(startPosSlider.getValue());
    }

	/*if (filePlayer->isPlaying() == false && button == &playButton)
	{
		startTimer(250);
	}

	if (filePlayer->isPlaying() == true && button == &playButton)
	{
		stopTimer();
	}*/
}

void FilePlayerGui::setFilePlayer (FilePlayer* fp)
{
    filePlayer = fp;
}

//FilenameComponentListener
void FilePlayerGui::filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged)
{
    if (fileComponentThatHasChanged == fileChooser.get())
    {
        File audioFile (fileChooser->getCurrentFile().getFullPathName());
        
        if(filePlayer != nullptr && audioFile.existsAsFile())
        {
            filePlayer->loadFile(audioFile);
			thumbnailComp.setFile(audioFile);
        }
        else
        {
            AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                         "Transport",
                                         "Couldn't open file!\n\n");
        }
    }
}

//Slider Listener
void FilePlayerGui::sliderValueChanged(Slider* slider)
{
	if (slider == &startPosSlider)
	{
		//DBG(startPosSlider.getValue());
		filePlayer->setPosition(startPosSlider.getValue());
		positionOverlay.setPosition(startPosSlider.getValue());
	}
	if (slider == &pitchSlider)
	{
		//DBG(pitchSlider.getValue());
		filePlayer->setPlaybackRate(pitchSlider.getValue());
	}
}

