#pragma once
#include "WaveformGui.h"


WaveformThumbnailComponent::WaveformThumbnailComponent (int sourceSamplesPerThumbnailSample,
														AudioFormatManager& formatManager,
														AudioThumbnailCache& cache) 
							: thumbnail(sourceSamplesPerThumbnailSample, formatManager, cache)
{
	thumbnail.addChangeListener(this);
}

WaveformThumbnailComponent::~WaveformThumbnailComponent()
{

}

void WaveformThumbnailComponent::setFile(const File& file)
{
	thumbnail.setSource(new FileInputSource(file));
}

void WaveformThumbnailComponent::paint(Graphics& g)
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

void WaveformThumbnailComponent::paintIfFileLoaded(Graphics& g)
{
	g.setColour(Colours::darkslategrey);
	thumbnail.drawChannels(g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 1.0f);
}

void WaveformThumbnailComponent::paintIfNoFileLoaded(Graphics& g)
{
	g.fillAll(Colours::white);
	g.setColour(Colours::darkgrey);
	g.drawFittedText("No File Loaded", getLocalBounds(), Justification::centred, 1);
}

void WaveformThumbnailComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &thumbnail) thumbnailChanged();
}

void WaveformThumbnailComponent::thumbnailChanged()
{
	repaint();
}

/************************************Position Overlay************************************************/

PlayheadPositionOverlay::PlayheadPositionOverlay()
{
	startTimer(40);
}

PlayheadPositionOverlay::~PlayheadPositionOverlay()
{
	stopTimer();
}

void PlayheadPositionOverlay::setPosition(double pos)
{
	position = pos;
}

void PlayheadPositionOverlay::setCrosshairColour(std::string colour)
{
	crosshairColour = colour;
}

void PlayheadPositionOverlay::paint(Graphics& g)
{
	if (position > 0.0)
	{
		auto drawPosition = position * getWidth();
		if (crosshairColour == "green")
		{
			g.setColour(Colours::green);
		}
		if (crosshairColour == "blue")
		{
			g.setColour(Colours::blue);
		}
		g.drawLine(drawPosition, 0.0f, drawPosition, (float)getHeight(), 1.0f);
	}
}

