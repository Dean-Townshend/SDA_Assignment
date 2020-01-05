#pragma once
#include "SamplePlayerGui.h"
#include "WaveformGui.h"

SamplePlayerGui::SamplePlayerGui(): startPositionOverlay(), thumbnailCache(5),
thumbnailComp(512, formatManager, thumbnailCache)
{
	//Button
    playButton.addListener (this);
    addAndMakeVisible (playButton);
    
	//File Chooser
    formatManager.registerBasicFormats();
	
    fileChooser = std::make_unique<FilenameComponent>("audiofile",
                                                       File(),
                                                       true, false, false,
                                                       formatManager.getWildcardForAllFormats(),
                                                       String(),
                                                       "(select audio file)");
    fileChooser->addListener (this);
    addAndMakeVisible (fileChooser.get());

	//Start slider
	startPosSlider.addListener(this);
	addAndMakeVisible(startPosSlider);
	startPosSlider.setSliderStyle(Slider::LinearHorizontal);
	startPosSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	startPosSlider.setRange(0.0, 1.0);
	startPosSlider.setTextValueSuffix(" S");
	startPosSlider.setNumDecimalPlacesToDisplay(3);

	//End
	endPosSlider.addListener(this);
	addAndMakeVisible(endPosSlider);
	endPosSlider.setSliderStyle(Slider::LinearHorizontal);
	endPosSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	endPosSlider.setRange(0.0, 1.0);
	endPosSlider.setTextValueSuffix(" S");
	endPosSlider.setNumDecimalPlacesToDisplay(3);

	//Pitch slider
	pitchSlider.addListener(this);
	addAndMakeVisible(pitchSlider);
	pitchSlider.setSliderStyle(Slider::Rotary);
	pitchSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	pitchSlider.setRange(0.1, 5.0);
	pitchSlider.setValue(0.1);
	pitchSlider.setTextValueSuffix(" %");
	pitchSlider.setNumDecimalPlacesToDisplay(3);

	//Labels
	startPosSliderLabel.setText("Start:", dontSendNotification);
	//startPosSliderLabel.attachToComponent(&startPosSlider, true);
	startPosSliderLabel.setColour(Label::textColourId, Colours::green);
	addAndMakeVisible(startPosSliderLabel);


	endPosSliderLabel.setText("End:", dontSendNotification);
	//endPosSliderLabel.attachToComponent(&endPosSlider, true);
	endPosSliderLabel.setColour(Label::textColourId, Colours::blue);
	addAndMakeVisible(endPosSliderLabel);

	//Waveform view
	addAndMakeVisible(&thumbnailComp);
	addAndMakeVisible(&startPositionOverlay);
	addAndMakeVisible(&endPositionOverlay);
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

	/**********************LEFT OF WINDOW**************************************************/

	const int NumElements = 3; //How many elements need to be mapped out 
	int heightPerEl = area.getHeight() / NumElements;

	Rectangle<int> leftArea = area.removeFromLeft(area.getWidth()/2);
	
	Rectangle<int> playButtArea = leftArea.removeFromTop(heightPerEl);
	Rectangle<int> fileChooseArea = leftArea.removeFromTop(heightPerEl);
	Rectangle<int> pitchControlArea = leftArea.removeFromBottom(heightPerEl);
	
	playButton.setBounds(playButtArea);
    fileChooser->setBounds (fileChooseArea);

	pitchSlider.setTextBoxStyle(Slider::TextBoxAbove, false, getWidth(), getHeight());
	pitchSlider.setBounds(pitchControlArea.removeFromLeft(pitchControlArea.getWidth()/2));

	/**********************RIGHT OF SCREEN************************************************/

	Rectangle<int> rightArea = area; //Remains of area
	Rectangle<int> waveform = rightArea.removeFromTop(rightArea.getHeight() * 0.8);

	Rectangle<int> startSliderArea = rightArea.removeFromTop(rightArea.getHeight() / 2);
	Rectangle<int> endSliderArea = rightArea; //Remains of right area

	Rectangle<int> startSliderAreaControls = startSliderArea.removeFromRight(startSliderArea.getWidth()*0.85);
	Rectangle<int> endSliderAreaControls = endSliderArea.removeFromRight(endSliderArea.getWidth()*0.85);

	startPosSlider.setBounds(startSliderAreaControls);
	endPosSlider.setBounds(endSliderAreaControls);

	//startPosSlider.setTextBoxStyle(Slider::TextBoxLeft, false, startSliderAreaC.getWidth(), startSliderAreaC.getHeight());
	//endPosSlider.setTextBoxStyle(Slider::TextBoxLeft, false, endSliderAreaC.getWidth(), endSliderAreaC.getHeight());

	startPosSliderLabel.setBounds(startSliderArea);
	endPosSliderLabel.setBounds(endSliderArea);

	startPositionOverlay.setBounds(waveform);
	endPositionOverlay.setBounds(waveform);
	
	startPositionOverlay.setCrosshairColour("green");
	endPositionOverlay.setCrosshairColour("blue");

	thumbnailComp.setBounds(waveform);
}


//Button Listener
void SamplePlayerGui::buttonClicked (Button* button)
{
    if (filePlayer != nullptr && button == &playButton)
    {
        filePlayer->setPlaying( ! filePlayer->isPlaying());
		filePlayer->setPosition(startPosSlider.getValue());
    }

	if (filePlayer->isPlaying() == false && button == &playButton)
	{
	
	}

	if (filePlayer->isPlaying() == true && button == &playButton)
	{
	
	}
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
		startPositionOverlay.setPosition(startPosSlider.getValue());
	}
	if (slider == &endPosSlider)
	{
		//DBG(startPosSlider.getValue());
		//filePlayer->setEndPosition(startPosSlider.getValue());
		endPositionOverlay.setPosition(endPosSlider.getValue());
	}
	if (slider == &pitchSlider)
	{
		//DBG(pitchSlider.getValue());
		filePlayer->setPlaybackRate(pitchSlider.getValue());
	}
}
