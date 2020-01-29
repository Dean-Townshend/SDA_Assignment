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

void FilePlayer::setEndPosition(double endPosition)
{
	transportEndPosition = audioTransportSource.getLengthInSeconds()* endPosition;
}

double FilePlayer::getPosition() const
{
	return audioTransportSource.getCurrentPosition();
}

double FilePlayer::getEndPosition() const
{
	return transportEndPosition;
}

double FilePlayer::getLength() const
{
	return audioTransportSource.getLengthInSeconds();
}

void FilePlayer::setPlaying (bool newState)//for start needs cahnging
{
	if (newState == true)
	{
		audioTransportSource.start();
	}
	else
    {
        audioTransportSource.stop();
    }

}

bool FilePlayer::getPlayState()//for start needs cahnging
{
	return playState;
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
	//DBG(levelSliderval);
}

void FilePlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    resamplingAudioSource->prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void FilePlayer::releaseResources()
{
    resamplingAudioSource->releaseResources();
}

void FilePlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{

	if (audioTransportSource.getCurrentPosition() >= transportEndPosition)
	{
		//audioTransportSource.setGain(0.5);
		audioTransportSource.stop();
		playState = false;
		bufferToFill.buffer->clear();
	}

	resamplingAudioSource->getNextAudioBlock(bufferToFill);

	//bufferToFill.buffer->reverse(bufferToFill.startSample, bufferToFill.numSamples);
	//bufferToFill.buffer->applyGain(0.5);	
	if (audioTransportSource.getCurrentPosition() >= transportEndPosition)
	{
		//audioTransportSource.setGain(0.5);
		audioTransportSource.stop();
		playState = false;
		bufferToFill.buffer->clear();
	}
}


