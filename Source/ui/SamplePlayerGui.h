#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../audio/FilePlayer.h"
#include "../audio/Audio.h"
#include "WaveformGui.h"

/** Gui for the FilePlayer class */
class SamplePlayerGui : public  Component,
                        private Button::Listener,
                        private FilenameComponentListener,
						private Slider::Listener
{
public:
	

    /** constructor - receives a reference to a FilePlayer object to control */
    SamplePlayerGui();
    
    /** Destructor */
    ~SamplePlayerGui();
    
    /** sets the file player that this gui controls */
    void setFilePlayer (FilePlayer* fp);
    
	void paint(Graphics& g) override;
    //Component
    void resized() override;

private:

	AudioFormatManager formatManager;

	//Button Listener
    void buttonClicked (Button* button) override;

	//Slider Listener
	void sliderValueChanged (Slider* slider) override;
    
    //FilenameComponentListener
    void filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged) override;
    
    TextButton playButton {"Play"};
    std::unique_ptr<FilenameComponent> fileChooser;
    
	FilePlayer* filePlayer {nullptr};

	Slider startPosSlider;
	Slider endPosSlider;

	Label startPosSliderLabel;
	Label endPosSliderLabel;

	Slider pitchSlider;

	PlayheadPositionOverlay startPositionOverlay;
	PlayheadPositionOverlay endPositionOverlay;

	AudioTransportSource transportSource;
	AudioThumbnailCache thumbnailCache;
	WaveformThumbnailComponent thumbnailComp;
	

};
