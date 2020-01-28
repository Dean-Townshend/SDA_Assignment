#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
//#include <string>


class WaveformThumbnailComponent : public Component,
								   private ChangeListener
{

public:

	WaveformThumbnailComponent (int sourceSamplesPerThumbnailSample,
								 AudioFormatManager& formatManager,
								 AudioThumbnailCache& cache);

	~WaveformThumbnailComponent();

	/** Sets the file that will be displayed.
		@param file reference to the file that will be used.
	*/
	void setFile(const File& file);

	/** Overidden, selects which paint function to called based on if a file is present or not.
	*/
	void paint(Graphics& g) override;

	/** Draws file not loaded if not file has been loaded
	*/
	void paintIfNoFileLoaded(Graphics& g);

	/** Draws the waveform based of the file that has been loaded
	*/
	void paintIfFileLoaded(Graphics& g);

	/** Overridden, checks if the source has changed.
	*/
	void changeListenerCallback(ChangeBroadcaster* source) override;

private:

	/** Calls repaint function 
	*/
	void thumbnailChanged();

	AudioThumbnail thumbnail;
};


/*****************************************Playhead Overlay**********************************************/

class PlayheadPositionOverlay : public Component,
								public Timer
{

public:

	//double position = 0;

	PlayheadPositionOverlay();
	
	~PlayheadPositionOverlay();
	
	/** Sets the position of the play head overlay.
		@param pos
	*/
	void setPosition(double pos);

	/** Sets the colour of the play head overlay.
		@param colour the colour that will be used.
	*/
	void setPlayHeadOverlayColour(std::string colour);

	/** Overidden, draws the play head overlay
	*/
	void paint(Graphics& g) override;
	
private:

	/** calls repaint function
	*/
	void timerCallback() override
	{
		repaint();
	}

	double position = 0;
	std::string crosshairColour;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayheadPositionOverlay)

};
