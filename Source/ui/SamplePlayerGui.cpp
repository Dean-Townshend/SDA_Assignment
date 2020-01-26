#pragma once
#include "SamplePlayerGui.h"
#include "WaveformGui.h"

SamplePlayerGui::SamplePlayerGui(): startPositionOverlay(), thumbnailCache(5),
thumbnailComp(512, formatManager, thumbnailCache)
{
	//Format Manager
	formatManager.registerBasicFormats();

	//Note name label
	nameLabel.setText("Note", dontSendNotification);
	nameLabel.setColour(Label::textColourId, Colours::darkslategrey);
	nameLabel.setColour(Label::outlineColourId, Colours::darkslategrey);
	nameLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(nameLabel);

	//Waveform view
	addAndMakeVisible(&thumbnailComp);
	addAndMakeVisible(&startPositionOverlay);
	addAndMakeVisible(&endPositionOverlay);

	//Start slider
	startPosSlider.addListener(this);
	addAndMakeVisible(startPosSlider);
	startPosSlider.setSliderStyle(Slider::LinearHorizontal);
	startPosSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	startPosSlider.setRange(0.0, 1.0);
	startPosSlider.setTextValueSuffix(" S");
	startPosSlider.setNumDecimalPlacesToDisplay(3);
	//Start position slider label
	startPosSliderLabel.setText("Start:", dontSendNotification);
	//startPosSliderLabel.attachToComponent(&startPosSlider, true);
	startPosSliderLabel.setColour(Label::textColourId, Colours::green);
	addAndMakeVisible(startPosSliderLabel);

	//End Slider
	endPosSlider.addListener(this);
	addAndMakeVisible(endPosSlider);
	endPosSlider.setSliderStyle(Slider::LinearHorizontal);
	endPosSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	endPosSlider.setRange(0.0, 1.0);
	endPosSlider.setTextValueSuffix(" S");
	endPosSlider.setNumDecimalPlacesToDisplay(3);
	//End position slider label
	endPosSliderLabel.setText("End:", dontSendNotification);
	endPosSliderLabel.setColour(Label::textColourId, Colours::blue);
	addAndMakeVisible(endPosSliderLabel);

	//Pitch slider
	pitchSlider.addListener(this);
	addAndMakeVisible(pitchSlider);
	pitchSlider.setSliderStyle(Slider::Rotary);
	pitchSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	pitchSlider.setRange(0.1, 5.0);
	pitchSlider.setValue(0.1);
	pitchSlider.setTextValueSuffix(" *");
	pitchSlider.setNumDecimalPlacesToDisplay(3);
	//Pitch slider label
	pitchSliderLabel.setText("Pitch", dontSendNotification);
	pitchSliderLabel.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(pitchSliderLabel);

	//Level Slider
	levelSlider.addListener(this);
	addAndMakeVisible(levelSlider);
	levelSlider.setSliderStyle(Slider::Rotary);
	levelSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	levelSlider.setRange(0.1, 5.0);
	levelSlider.setValue(0.1);
	levelSlider.setTextValueSuffix(" *");
	levelSlider.setNumDecimalPlacesToDisplay(3);
	//Level slider label
	levelSliderLabel.setText("Fine Pitch", dontSendNotification);
	levelSliderLabel.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(levelSliderLabel);

	//Button
	playButton.addListener(this);
	addAndMakeVisible(playButton);

	//File chooser
	fileChooser = std::make_unique<FilenameComponent>("audiofile",
		File(),
		true, false, false,
		formatManager.getWildcardForAllFormats(),
		String(),
		"(select audio file)");
	fileChooser->addListener(this);
	addAndMakeVisible(fileChooser.get());

}

SamplePlayerGui::~SamplePlayerGui()
{
    
}

void SamplePlayerGui::paint(Graphics& g)
{

}

//Layout of components
void SamplePlayerGui::resized()
{
	Rectangle<int> area = getLocalBounds(); //area rectangle is used to map out each element of the control section

	//Note name label that changes on which pad is selected 
	Rectangle<int> nameArea = area.removeFromTop(area.getHeight() * 0.05);
	nameLabel.setBounds(nameArea);

	/*********************************************Controls*************************************************************/
	Rectangle<int> controlArea = area.removeFromBottom(area.getHeight()*0.5);
	Rectangle<int> playArea = controlArea.removeFromBottom(controlArea.getHeight() * 0.3);
	Rectangle<int> playButtArea = playArea.removeFromTop(playArea.getHeight()*0.6);
	Rectangle<int> fileChooseArea = playArea;
	playButton.setBounds(playButtArea);
	fileChooser->setBounds(fileChooseArea);

	Rectangle<int> SliderArea = controlArea;
	Rectangle<int> pitchArea = SliderArea.removeFromLeft(SliderArea.getWidth()/2);
	Rectangle<int> levelSliderArea = SliderArea;
	Rectangle<int> pitchLabelArea = pitchArea.removeFromBottom(levelSliderArea.getHeight() * 0.4);
	Rectangle<int> levelLabelArea = levelSliderArea.removeFromBottom(levelSliderArea.getHeight()*0.4);

	pitchSlider.setTextBoxStyle(Slider::TextBoxBelow, false, pitchArea.getWidth(), pitchArea.getHeight() / 4);
	levelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, levelSliderArea.getWidth(), levelSliderArea.getHeight() / 4);
	
	pitchSlider.setBounds(pitchArea);
	levelSlider.setBounds(levelSliderArea);
	pitchSliderLabel.setBounds(pitchLabelArea);
	pitchSliderLabel.setJustificationType(Justification::centred);
	levelSliderLabel.setBounds(levelLabelArea);
	levelSliderLabel.setJustificationType(Justification::centred);

	/************************************************Waveform View*************************************************************/

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

void SamplePlayerGui::setNameLabelText(String name)
{
	nameLabel.setText(name, dontSendNotification);
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
		endPositionOverlay.setPosition(endPosSlider.getValue());
	}
	if (slider == &pitchSlider)
	{
		//DBG(pitchSlider.getValue());
		filePlayer->setPlaybackRate(pitchSlider.getValue());
	}
}

