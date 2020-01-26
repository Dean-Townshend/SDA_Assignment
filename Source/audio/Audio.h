#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FilePlayer.h"
#include <array>

/** Class containing all audio processes */

class Audio : public MidiInputCallback, 
					 AudioIODeviceCallback
{
public:
	enum
	{
		NumOfFilePlayers = 8
	};

	/** Constructor */
	Audio();

	/** Destructor */
	~Audio();

	/** returns a pointer to the file player */
	FilePlayer* getFilePlayer(int playerNum);

	/** Returns the audio device manager, don't keep a copy of it! */
	AudioDeviceManager& getAudioDeviceManager() { return audioDeviceManager; }

	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;

	void audioDeviceIOCallback(const float** inputChannelData,
		int numInputChannels,
		float** outputChannelData,
		int numOutputChannels,
		int numSamples) override;
	void audioDeviceAboutToStart(AudioIODevice* device) override;
	void audioDeviceStopped() override;

	void setReverbParam(double wetdryLevel);
	void setLevel(float levelSliderval);

private:
	
	std::array <FilePlayer, NumOfFilePlayers> filePlayer;
	AudioDeviceManager audioDeviceManager;
	AudioSourcePlayer audioSourcePlayer;
	MixerAudioSource mixer;
	ReverbAudioSource verbUnit;
	Reverb::Parameters verbParams;

	float levelVal;
	

	


};