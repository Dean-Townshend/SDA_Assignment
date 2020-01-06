#include "Audio.h"

Audio::Audio()
{
    audioDeviceManager.initialiseWithDefaultDevices (1, 2); //1 inputs, 2 outputs
    
	for (int i = 0; i < NumOfFilePlayers; i++)
	{
		mixer.addInputSource(&filePlayer[i], false);
	}

    //set the filePlayer as the audio source
    audioSourcePlayer.setSource (&mixer);
    
    audioDeviceManager.addMidiInputCallback (String(), this);
    audioDeviceManager.addAudioCallback (this);
}

Audio::~Audio()
{
    audioDeviceManager.removeAudioCallback (this);
    audioDeviceManager.removeMidiInputCallback (String(), this);
    
    //remove the file player from the source
    audioSourcePlayer.setSource (nullptr);

	mixer.removeAllInputs();
}

FilePlayer* Audio::getFilePlayer(int playerNum)
{
	return &filePlayer[playerNum];
}

void Audio::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
	if (message.isNoteOn())
	{
		DBG( message.getNoteNumber());

		if (message.getNoteNumber() == 60)
		{
			filePlayer[0].setPlaying(true);
		}

		if (message.getNoteNumber() == 61)
		{
			filePlayer[1].setPlaying(true);
		}
		if (message.getNoteNumber() == 62)
		{
			filePlayer[2].setPlaying(true);
		}
		if (message.getNoteNumber() == 64)
		{
			filePlayer[3].setPlaying(true);
		}
		
	}


}

void Audio::audioDeviceIOCallback (const float** inputChannelData,
                                           int numInputChannels,
                                           float** outputChannelData,
                                           int numOutputChannels,
                                           int numSamples)
{
    // get the audio from our file player - player puts samples in the output buffer
    audioSourcePlayer.audioDeviceIOCallback (inputChannelData, numInputChannels, outputChannelData, numOutputChannels, numSamples);
    
    //All audio processing is done here
    const float* inL = inputChannelData[0];

    float *outL = outputChannelData[0];
    float *outR = outputChannelData[1];
    
    while(numSamples--)
    {
        float fileOutL = *outL;
        float fileOutR = *outR;
        
        *outL = fileOutL;
        *outR = fileOutR;
        
        inL++;
        outL++;
        outR++;
    }
}


void Audio::audioDeviceAboutToStart (AudioIODevice* device)
{
    audioSourcePlayer.audioDeviceAboutToStart (device);
}

void Audio::audioDeviceStopped()
{
    audioSourcePlayer.audioDeviceStopped();
}
