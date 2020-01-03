#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SimpleThumbnailComponent : public Component,
								 private ChangeListener
{

public:

	

	SimpleThumbnailComponent (int sourceSamplesPerThumbnailSample,
								 AudioFormatManager& formatManager,
								 AudioThumbnailCache& cache);

	~SimpleThumbnailComponent();

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

class SimplePositionOverlay : public Component,
							  public Timer
{

public:

	//double position = 0;

	SimplePositionOverlay();
	
	~SimplePositionOverlay();
	
	void setPosition(double pos);

	void paint(Graphics& g) override;
	
private:

	void timerCallback() override
	{
		repaint();
	}

	double position = 0;

	//double *ip = &position;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimplePositionOverlay)

};

//------------------------------------------------------------------------------