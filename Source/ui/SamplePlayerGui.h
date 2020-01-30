#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../audio/FilePlayer.h"
#include "../audio/Audio.h"
#include "WaveformGui.h"

/** Gui for the FilePlayer class.
 @see FilePlayer
 */
class FilePlayerGui : public  Component,
                      private Button::Listener,
                      private FilenameComponentListener,
					  private Slider::Listener
						
{

public:
	
	/** Constructor */
    FilePlayerGui();
    
    /** Destructor */
    ~FilePlayerGui();
    
    /** Sets the file player*/
    void setFilePlayer (FilePlayer* fp);
    
    /** Sets the text of the name label */
	void setNameLabelText(String name);
    
    /** This function positions all of the file player gui components*/
    void resized() override;

private:

    //Listeners
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
