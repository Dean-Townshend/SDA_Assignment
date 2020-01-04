#pragma once
#include "SamplePlayerGui.h"
#include "WaveformGui.h"

SamplePlayerGui::SamplePlayerGui(): positionOverlay(), thumbnailCache(5),
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
	startPosSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	startPosSlider.setRange(0.0, 1.0);

	//Pitch slider
	pitchSlider.addListener(this);
	addAndMakeVisible(pitchSlider);
	pitchSlider.setSliderStyle(Slider::LinearHorizontal);
	pitchSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	pitchSlider.setRange(0.1, 5.0);
	pitchSlider.setValue(0.1);

	//Waveform view
	addAndMakeVisible(&thumbnailComp);
	addAndMakeVisible(&positionOverlay);
}

SamplePlayerGui::~SamplePlayerGui()
{
    
}

void SamplePlayerGui::paint(Graphics& g)
{

}

//Component
void SamplePlayerGui::resized()
{
	Rectangle<int> area = getLocalBounds(); //Rectangle is used to map out each element of the file player

	const int NumElements = 3; //How many elements need to be mapped out 
	int heightPerEl = area.getHeight() / NumElements;

	Rectangle<int> controlArea = area.removeFromLeft(area.getWidth()/2);
	Rectangle<int> waveformArea = area;

	Rectangle<int> waveform = waveformArea.removeFromTop(waveformArea.getHeight() * 0.80);
	Rectangle<int> waveformSlider = waveformArea;

	positionOverlay.setBounds(waveform);
	thumbnailComp.setBounds(waveform);
	
	Rectangle<int> playButtArea = controlArea.removeFromTop(heightPerEl);
	Rectangle<int> fileChooseArea = controlArea.removeFromTop(heightPerEl);
	Rectangle<int> pitchSliderArea = controlArea.removeFromBottom(heightPerEl);
	//Rectangle<int> startSliderArea = controlArea.removeFromBottom(heightPerEl);
	
	playButton.setBounds(playButtArea);
    fileChooser->setBounds (fileChooseArea);
	startPosSlider.setBounds(waveformArea);
	pitchSlider.setBounds(pitchSliderArea);
}


//Button Listener
void SamplePlayerGui::buttonClicked (Button* button)
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

void SamplePlayerGui::setFilePlayer (FilePlayer* fp)
{
    filePlayer = fp;
}

//FilenameComponentListener
void SamplePlayerGui::filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged)
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
void SamplePlayerGui::sliderValueChanged(Slider* slider)
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

