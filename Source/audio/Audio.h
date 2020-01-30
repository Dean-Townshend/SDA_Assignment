#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"
#include "FilePlayer.h"
#include <array>

/** Class responsible for all of the audio processes.
 
		This Classs runs on a high priority thread required 
		to maintain clean audio, therefore GUI processes should not be perfomed here.
 
        For overidden functions, see JUCE framework documentation.
*/
class Audio : public MidiInputCallback, 
					 AudioIODeviceCallback
{
public:

	//this is used to determine how many filePlayer objects and pad buttons are created.
	enum
	{
		NumOfFilePlayers = 8
	};

	/** Constructor */
	Audio();

	/** Destructor */
	~Audio();

	/** returns a pointer to the file player.
		@param playerNum	Used to determine which filePlayer reference is return. 
	*/
	FilePlayer* getFilePlayer(int playerNum);

	/** Returns The audio device manager.
		@return audioDeviceManager 
	*/
	AudioDeviceManager& getAudioDeviceManager() { return audioDeviceManager; }

	/** Overidden, Handles MIDI Messages.
		Plays fileplayers of corresponding MIDI notes.
	*/
	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;

	/** Overidden, Outputs audio samples.
	*/
	void audioDeviceIOCallback(const float** inputChannelData,
							   int numInputChannels,
							   float** outputChannelData,
							   int numOutputChannels,
							   int numSamples) override;

	/** Overidden, calls audioSourcesPlayer's audioDeviceAboutToStart function.
	*/
	void audioDeviceAboutToStart(AudioIODevice* device) override;

	/** Overidden, calles audioSourcesPlayer's audioDeviceStopped function.
	*/
	void audioDeviceStopped() override;

	/** Sets the parameters of the reverb effect.
			@param wetDryLevel used to set the ratio of wet and dry of the reverb unit.
			@param	roomSize sets the size of room in the reveb unit.
	*/
	void setReverbParam(double wetDryLevel, double roomSize);

	/** Sets overall gain.
			@param  levelSliderVal sets gain multipayer to the overal level of the audioSourcePlayer 0.0 - 1.0.
	*/
	void setLevel(float levelSliderVal);

private:
	

	AudioDeviceManager audioDeviceManager;
	std::array <FilePlayer, NumOfFilePlayers> filePlayer; //Array of individual FilePlayer objects.
	AudioSourcePlayer audioSourcePlayer;				  //The outermost source player 
	MixerAudioSource mixer;								  //Used to mix all of the individual players
	ReverbAudioSource verbUnit;							  //Used to apply reverb to the audioSourcePlayer
	Reverb::Parameters verbParams;						  //Structure containg reverb parameter, used to set reverb params

	float levelVal = 0.5;								  //Float used to store audioSourcePlayer level 

};
