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
							  private Timer
{

public:

	SimplePositionOverlay(AudioTransportSource& transportSourceToUse);
	
	~SimplePositionOverlay();
	
	void paint(Graphics& g) override;
	
	void mouseDown(const MouseEvent& event) override;

private:

	void timerCallback() override;
	AudioTransportSource& transportSource;
};

//------------------------------------------------------------------------------