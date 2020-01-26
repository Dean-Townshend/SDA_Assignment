#include "Audio.h"

Audio::Audio() : verbUnit(&mixer, false)
{
    audioDeviceManager.initialiseWithDefaultDevices (0, 2); //1 inputs, 2 outputs
    
	for (int i = 0; i < NumOfFilePlayers; i++)
	{
		mixer.addInputSource(&filePlayer[i], false);
	}	

	verbParams.damping = 0.0;
	verbParams.freezeMode = 0.1;
	verbParams.roomSize = 0.5;
	verbParams.width = 0.5;
	verbParams.wetLevel = 0.0;
	verbParams.dryLevel = 1.0;
	verbUnit.setParameters(verbParams);

    audioSourcePlayer.setSource (&verbUnit);
    
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
		if (message.getNoteNumber() == 62)
		{
			filePlayer[1].setPlaying(true);
		}
		if (message.getNoteNumber() == 64)
		{
			filePlayer[2].setPlaying(true);
		}
		if (message.getNoteNumber() == 66)
		{
			filePlayer[3].setPlaying(true);
		}
		if (message.getNoteNumber() == 68)
		{
			filePlayer[4].setPlaying(true);
		}
		if (message.getNoteNumber() == 70)
		{
			filePlayer[5].setPlaying(true);
		}
		if (message.getNoteNumber() == 72)
		{
			filePlayer[6].setPlaying(true);
		}
		if (message.getNoteNumber() == 74)
		{
			filePlayer[7].setPlaying(true);
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
        
        *outL = fileOutL *levelVal;
        *outR = fileOutR *levelVal;
        
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

void Audio::setReverbParam (double wetdryLevel)
{
	verbParams.damping = 0.0;
	verbParams.freezeMode = 0.1;
	verbParams.roomSize = 0.5;
	verbParams.width = 0.5;

	verbParams.wetLevel = wetdryLevel;
	verbParams.dryLevel = ((wetdryLevel - 0.0) / (1.0 - 0.0)) * (0.0 - 1.0) + 1.0;
	DBG(verbParams.dryLevel);
	DBG(verbParams.wetLevel);

	verbUnit.setParameters(verbParams);
}

void Audio::setLevel(float levelSliderval)
{
	levelVal = levelSliderval;
	DBG(levelSliderval);
}
