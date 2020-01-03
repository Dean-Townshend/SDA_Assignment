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
		Rectangle<int> k = getLocalBounds();
		Rectangle<float> b = k.toFloat();

		//g.fillAll(Colours::red);

		g.setColour(Colours::red);

		//g.fillRect(b);

		//g.fillAll(Colours::blue);
		//g.fillRect(b);


		auto drawPosition = position * getWidth();

		g.setColour(Colours::red);
		g.drawLine(drawPosition, 0.0f, drawPosition, (float)getHeight(), 1.0f);
		//g.drawRect(drawPosition, 0.0f, 0.0f, (float)getHeight(), 0.5f);
		
	}

	/*if (position > 0.0)
	{
		g.setColour(Colours::green);

		Rectangle<int> p = getLocalBounds();

		int h = p.getHeight();
		int b = p.getBottom();
		int w = p.getWidth();

		auto drawPosition = (float)w * position;

		g.drawRect(drawPosition, 0, 1, h, 4);

		DBG(position);
	}*/

}

