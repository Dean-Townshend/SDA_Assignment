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
	pitchSlider.setTextValueSuffix(" *");
	pitchSlider.setNumDecimalPlacesToDisplay(3);

	finePitchSlider.addListener(this);
	addAndMakeVisible(finePitchSlider);
	finePitchSlider.setSliderStyle(Slider::Rotary);
	finePitchSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	finePitchSlider.setRange(0.1, 5.0);
	finePitchSlider.setValue(0.1);
	finePitchSlider.setTextValueSuffix(" *");
	finePitchSlider.setNumDecimalPlacesToDisplay(3);

	//Labels
	nameLabel.setText("Name", dontSendNotification);
	//startPosSliderLabel.attachToComponent(&startPosSlider, true);
	nameLabel.setColour(Label::textColourId, Colours::darkslategrey);
	nameLabel.setColour(Label::outlineColourId, Colours::darkslategrey);
	nameLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(nameLabel);


	startPosSliderLabel.setText("Start:", dontSendNotification);
	//startPosSliderLabel.attachToComponent(&startPosSlider, true);
	startPosSliderLabel.setColour(Label::textColourId, Colours::green);
	addAndMakeVisible(startPosSliderLabel);


	endPosSliderLabel.setText("End:", dontSendNotification);
	//endPosSliderLabel.attachToComponent(&endPosSlider, true);
	endPosSliderLabel.setColour(Label::textColourId, Colours::blue);
	addAndMakeVisible(endPosSliderLabel);

	pitchSliderLabel.setText("Pitch", dontSendNotification);
	pitchSliderLabel.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(pitchSliderLabel);

	finePitchSliderLabel.setText("Fine Pitch", dontSendNotification);
	finePitchSliderLabel.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(finePitchSliderLabel);

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

	Rectangle<int> nameArea = area.removeFromTop(area.getHeight() * 0.05);

	/**********************Top**************************************************/
	Rectangle<int> topArea = area.removeFromBottom(area.getHeight()*0.5);
	
	Rectangle<int> playArea = topArea.removeFromBottom(topArea.getHeight() * 0.3);

	Rectangle<int> playButtArea = playArea.removeFromTop(playArea.getHeight()*0.6);
	Rectangle<int> fileChooseArea = playArea;

	Rectangle<int> pitchControlArea = topArea;

	Rectangle<int> pitchArea = pitchControlArea.removeFromLeft(pitchControlArea.getWidth()/2);
	Rectangle<int> finePitchArea = pitchControlArea;

	Rectangle<int> pitchLabelArea = pitchArea.removeFromBottom(finePitchArea.getHeight() * 0.4);
	Rectangle<int> finePitchLabelArea = finePitchArea.removeFromBottom(finePitchArea.getHeight()*0.4);

	nameLabel.setBounds(nameArea);

	playButton.setBounds(playButtArea);
    fileChooser->setBounds (fileChooseArea);
	
	pitchSlider.setBounds(pitchArea);
	finePitchSlider.setBounds(finePitchArea);

	pitchSlider.setTextBoxStyle(Slider::TextBoxAbove, false, pitchArea.getWidth(), pitchArea.getHeight() / 4);
	finePitchSlider.setTextBoxStyle(Slider::TextBoxAbove, false, finePitchArea.getWidth(), finePitchArea.getHeight() / 4);
	
	pitchSliderLabel.setBounds(pitchLabelArea);
	pitchSliderLabel.setJustificationType(Justification::centred);
	finePitchSliderLabel.setBounds(finePitchLabelArea);
	finePitchSliderLabel.setJustificationType(Justification::centred);

	/**********************Thumb************************************************/

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
		DBG("tiggered");
        filePlayer->setPlaying( ! filePlayer->isPlaying());
		filePlayer->setPosition(startPosSlider.getValue());
    }

	/*if (filePlayer->isPlaying() == false && button == &playButton)
	{
	
	}

	if (filePlayer->isPlaying() == true && button == &playButton)
	{
	
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

