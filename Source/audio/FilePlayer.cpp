#include "FilePlayer.h"

FilePlayer::FilePlayer() : thread("FilePlayThread")
{
	resamplingAudioSource = std::make_unique<ResamplingAudioSource>(&audioTransportSource, false);
	thread.startThread();
}
	
FilePlayer::~FilePlayer()
{
	resamplingAudioSource->releaseResources();
    audioTransportSource.setSource (nullptr);   
    thread.stopThread (100);
}

void FilePlayer::setPosition(double newPosition)
{
	audioTransportSource.setPosition(audioTransportSource.getLengthInSeconds() * newPosition);
}

double FilePlayer::getPosition()
{
	return audioTransportSource.getCurrentPosition();
}

double FilePlayer::getLength()
{
	return audioTransportSource.getLengthInSeconds();
}

void FilePlayer::setPlaying (bool newState)//for start needs cahnging
{
    if(newState == true)
    {
        //audioTransportSource.setPosition (0.0);
        audioTransportSource.start();
    }
    else
    {
        audioTransportSource.stop();
    }
}

bool FilePlayer::isPlaying () const
{
    return audioTransportSource.isPlaying();
}

void FilePlayer::loadFile(const File& newFile)
{
    // unload the previous file source and delete it..
    setPlaying (false);
    audioTransportSource.setSource (nullptr);
    
    // create a new file source from the file..
    // get a format manager and set it up with the basic types (wav, ogg and aiff).
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    if (auto reader = formatManager.createReaderFor (newFile))
    {
        //currentFile = audioFile;
        currentAudioFileSource = std::make_unique<AudioFormatReaderSource> (reader, true);
        
        // ..and plug it into our transport source
        audioTransportSource.setSource (currentAudioFileSource.get(),
                                   32768, // tells it to buffer this many samples ahead
                                   &thread,
                                   reader->sampleRate);
    }
}

void FilePlayer::setAdsrSampleRate(double sampleRate)
{
	envelope.setSampleRate(sampleRate);
}

void FilePlayer::setPlaybackRate(double newRate)
{
	resamplingAudioSource->setResamplingRatio(newRate);
}

void FilePlayer::setLevel(double levelSliderval)
{
	audioTransportSource.setGain(levelSliderval);
	DBG(levelSliderval);
}

void FilePlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    resamplingAudioSource->prepareToPlay (samplesPerBlockExpected, sampleRate);
	envelope.setSampleRate(sampleRate);
}

void FilePlayer::releaseResources()
{
    resamplingAudioSource->releaseResources();
}

void FilePlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{

	/*auto* device = audioTransportSource->deviceManager.getCurrentAudioDevice();
	auto activeInputChannels = device->getActiveInputChannels();
	auto activeOutputChannels = device->getActiveOutputChannels();
	auto maxInputChannels = activeInputChannels.getHighestBit() + 1;
	auto maxOutputChannels = activeOutputChannels.getHighestBit() + 1;*/

	//auto level = (float)levelVal;

	//for (auto channel = 0; channel < 1; ++channel)
	//{
	//	if ((!activeOutputChannels[channel]) || maxInputChannels == 0)
	//	{
	//		bufferToFill.buffer->clear(channel, bufferToFill.startSample, bufferToFill.numSamples);
	//	}
	//	else
	//	{
	//		auto actualInputChannel = channel % maxInputChannels; // [1]

	//		if (!activeInputChannels[channel]) // [2]
	//		{
	//			bufferToFill.buffer->clear(channel, bufferToFill.startSample, bufferToFill.numSamples);
	//		}
	//		else // [3]
	//		{
	//			auto* inBuffer = bufferToFill.buffer->getReadPointer(actualInputChannel,
	//				bufferToFill.startSample);
	//			auto* outBuffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

	//			for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
	//				outBuffer[sample] = inBuffer[sample] * random.nextFloat() * level;
	//		}
	//	}
	//}
	
	//AudioSourceChannelInfo bufferToFill2 (bufferToFill);
	////bufferToFill2.clearActiveBufferRegion();

	//int start = bufferToFill2.startSample;
	//int num = bufferToFill2.numSamples;

	//int* ptr = &bufferToFill2.buffer;

	//envelope.applyEnvelopeToBuffer(*bufferToFill2.buffer, start, num);

	//bufferToFill2.buffer->reverse(bufferToFill.startSample, bufferToFill.numSamples);

	/*for (int sample = 0; sample < bufferToFill2.buffer->getNumSamples(); sample++)
	{
		bufferToFill2.buffer->getSample(1, sample) * levelVal;
		bufferToFill2.buffer->getSample(0, sample) * levelVal;
	}*/
	

	resamplingAudioSource->getNextAudioBlock (bufferToFill);
}


