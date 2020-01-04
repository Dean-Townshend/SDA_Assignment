#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class WaveformThumbnailComponent : public Component,
								   private ChangeListener
{

public:

	

	WaveformThumbnailComponent (int sourceSamplesPerThumbnailSample,
								 AudioFormatManager& formatManager,
								 AudioThumbnailCache& cache);

	~WaveformThumbnailComponent();

	void setFile(const File& file);

	void paint(Graphics& g) override;

	void paintIfNoFileLoaded(Graphics& g);

	void paintIfFileLoaded(Graphics& g);

	void changeListenerCallback(ChangeBroadcaster* source) override;

private:

	void thumbnailChanged();

	AudioThumbnail thumbnail;
};


//------------------------------------------------------------------------------

class PlayheadPositionOverlay : public Component,
								public Timer
{

public:

	//double position = 0;

	PlayheadPositionOverlay();
	
	~PlayheadPositionOverlay();
	
	void setPosition(double pos);

	void paint(Graphics& g) override;
	
private:

	void timerCallback() override
	{
		repaint();
	}

	double position = 0;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayheadPositionOverlay)

};

//------------------------------------------------------------------------------