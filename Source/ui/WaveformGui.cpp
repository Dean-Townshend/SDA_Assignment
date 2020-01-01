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
	g.fillAll(Colours::white);

	g.setColour(Colours::red);
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

SimplePositionOverlay::SimplePositionOverlay(AudioTransportSource& transportSourceToUse)
											: transportSource(transportSourceToUse)
{
	startTimer(40);
}

SimplePositionOverlay::~SimplePositionOverlay()
{

}

void SimplePositionOverlay::paint(Graphics& g)
{
	auto duration = (float)transportSource.getLengthInSeconds();

	if (duration > 0.0)
	{
		auto audioPosition = (float)transportSource.getCurrentPosition();
		auto drawPosition = (audioPosition / duration) * getWidth();

		g.setColour(Colours::green);
		g.drawLine(drawPosition, 0.0f, drawPosition, (float)getHeight(), 2.0f);
	}
}

void SimplePositionOverlay::mouseDown(const MouseEvent& event)
{
	auto duration = transportSource.getLengthInSeconds();

	if (duration > 0.0)
	{
		auto clickPosition = event.position.x;
		auto audioPosition = (clickPosition / getWidth()) * duration;

		transportSource.setPosition(audioPosition);
	}
}

void SimplePositionOverlay::timerCallback()
{
	repaint();
}