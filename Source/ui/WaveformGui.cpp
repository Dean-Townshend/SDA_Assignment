#pragma once
#include "WaveformGui.h"


SimpleThumbnailComponent::SimpleThumbnailComponent (int sourceSamplesPerThumbnailSample,
							 AudioFormatManager& formatManager,
							 AudioThumbnailCache& cache) 
							: thumbnail(sourceSamplesPerThumbnailSample, formatManager, cache)
{
	thumbnail.addChangeListener(this);
}

SimpleThumbnailComponent::~SimpleThumbnailComponent()
{

}

void SimpleThumbnailComponent::setFile(const File& file)
{
	thumbnail.setSource(new FileInputSource(file));
}

void SimpleThumbnailComponent::paint(Graphics& g)
{
	if (thumbnail.getNumChannels() == 0)
	{
		paintIfNoFileLoaded(g);
	}
	else
	{
		paintIfFileLoaded(g);
	}
}

void SimpleThumbnailComponent::paintIfFileLoaded(Graphics& g)
{
	g.fillAll(Colours::grey);

	g.setColour(Colours::darkslategrey);
	thumbnail.drawChannels(g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 1.0f);
}

void SimpleThumbnailComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &thumbnail)
		thumbnailChanged();
}

void SimpleThumbnailComponent::paintIfNoFileLoaded(Graphics& g)
{
	g.fillAll(Colours::white);
	g.setColour(Colours::darkgrey);
	g.drawFittedText("No File Loaded", getLocalBounds(), Justification::centred, 1);
}

void SimpleThumbnailComponent::thumbnailChanged()
{
	repaint();
}


/******************************Position Overlay*****************************************/

SimplePositionOverlay::SimplePositionOverlay()
{
	startTimer(40);
}

SimplePositionOverlay::~SimplePositionOverlay()
{

}

void SimplePositionOverlay::setPosition(double pos)
{
	position = pos;
}

void SimplePositionOverlay::paint(Graphics& g)
{
	if (position > 0.0)
	{
		auto drawPosition = position * getWidth();
		g.setColour(Colours::white);
		g.drawLine(drawPosition, 0.0f, drawPosition, (float)getHeight(), 1.0f);
	}
}

