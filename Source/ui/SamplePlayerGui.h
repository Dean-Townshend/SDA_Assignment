#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../audio/FilePlayer.h"
#include "../audio/Audio.h"
#include "WaveformGui.h"

/** Gui for the FilePlayer class */
class FilePlayerGui : public  Component,
					  public  Timer,
                      private Button::Listener,
                      private FilenameComponentListener,
					  private Slider::Listener
						
{

public:
	
	/** Constructor */
    FilePlayerGui();
    
    /** Destructor */
    ~FilePlayerGui();
    

    void setFilePlayer (FilePlayer* fp);

	void setNameLabelText(String name);
    
	void paint(Graphics& g) override;
    
    void resized() override;

	void timerCallback()override;

private:

	void buttonClicked (Button* button) override; //Button Listener
	void sliderValueChanged (Slider* slider) override; //Slider Listener
    void filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged) override; //FilenameComponentListener
	
    
	FilePlayer* filePlayer{ nullptr };
	AudioFormatManager formatManager;    
	AudioTransportSource transportSource;

	//Gui Components 
	Label currentPadLabel;
	//Waveform view
	PlayheadPositionOverlay startPositionOverlay;
	PlayheadPositionOverlay endPositionOverlay;
	AudioThumbnailCache thumbnailCache;
	WaveformThumbnailComponent thumbnailComp;
	//Controls
	Slider startPosSlider;
	Slider endPosSlider;
	Label startPosSliderLabel;
	Label endPosSliderLabel;
	Slider pitchSlider;
	Label pitchSliderLabel;
	Slider levelSlider;
	Label levelSliderLabel;
	TextButton padTriggerButton{ "Trigger" };
	std::unique_ptr<FilenameComponent> fileChooser;

};
