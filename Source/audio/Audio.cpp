#include "Audio.h"

Audio::Audio()
{
    audioDeviceManager.initialiseWithDefaultDevices (1, 2); //1 inputs, 2 outputs
    
    //set the filePlayer as the audio source
    audioSourcePlayer.setSource (&filePlayer[0]);
    
    audioDeviceManager.addMidiInputCallback (String(), this);
    audioDeviceManager.addAudioCallback (this);
}

Audio::~Audio()
{
    audioDeviceManager.removeAudioCallback (this);
    audioDeviceManager.removeMidiInputCallback (String(), this);
    
    //remove the file player from the source
    audioSourcePlayer.setSource (nullptr);
}

FilePlayer* Audio::getFilePlayer()
{
	return &filePlayer[0];
}

void Audio::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
    //All MIDI inputs arrive here

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
