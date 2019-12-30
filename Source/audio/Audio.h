/*
  ==============================================================================

    Audio.h
    Author:  Tom Mitchell

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FilePlayer.h"

/** Class containing all audio processes */

class Audio :   public MidiInputCallback,
                public AudioIODeviceCallback
{
public:
    /** Constructor */
    Audio();
    
    /** Destructor */
    ~Audio();
    
    /** returns a pointer to the file player */
    FilePlayer* getFilePlayer();
    
    /** Returns the audio device manager, don't keep a copy of it! */
    AudioDeviceManager& getAudioDeviceManager() { return audioDeviceManager; }
    
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
    
    void audioDeviceIOCallback (const float** inputChannelData,
                                int numInputChannels,
                                float** outputChannelData,
                                int numOutputChannels,
                                int numSamples) override;
    void audioDeviceAboutToStart (AudioIODevice* device) override;
    void audioDeviceStopped() override;
private:
    AudioDeviceManager audioDeviceManager;
    AudioSourcePlayer audioSourcePlayer;
    FilePlayer filePlayer;
};
