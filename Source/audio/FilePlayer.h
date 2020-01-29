#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

/** Streams audio from a file.
	
	For overidden functions, see JUCE framework documentation.

*/
class FilePlayer :  public AudioSource
{
public:

    /** Constructor */
    FilePlayer();
    
    /** Destructor */
    ~FilePlayer();
    
    /** Starts or stops playback of the looper.
			@param newState used to determine whether to play or stop audioTransportSource
	*/
    void setPlaying (bool newState);
    
    /** Gets the current playback state of the audioTransportSource. */
    bool isPlaying() const;
    
    /** Loads the specified file into the transport source.
			@param newFile reference to file to be used by audioTransportSource.
	*/
    void loadFile (const File& newFile);
    
	/** Overidden, calls resamplingAudioSources' prepareToPlay function.
	*/
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;

	/** Overidden, calls resamplingAudioSources' releaseResources function.
	*/
    void releaseResources() override;

	/** Overidden, calls resamplingAudioSources' getNextAudioBlock function and processes bufferToFill.
	*/
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;

	/** Sets the current position of the audioTransportSource.
			@param newPosition used to set the position of audioTransportSource.
	*/
	void setPosition(double newPosition);

	/** Sets the end position of the audioTransportSource.
			@param endPosition used to set the point at which audioTransportSource stops.
	*/
	void setEndPosition(double endPosition);

	/** Gets the current position of the audioTransportSource.
	*/
	double getPosition() const;

	/** Gets the end position of the filePlayer.
	*/
	double getEndPosition() const;

	/** Gets the length of the file loaded in the audioTransportSource.
	*/
	double getLength() const;

	/** Sets the end position of the audioTransportSource.
			@param newRate used to set the resampling ratio.
	*/
	void setPlaybackRate(double newRate);

	/** Sets the gain of audioTransportSource.
			@param levelSliderVal used to set the resampling ratio.
	*/
	void setLevel(double levelSliderVal);

private:

	/** Sets the ADSR samplerate.
			@param sampleRate used to set the sample rate of the ADSR object.
	*/

	void setAdsrSampleRate(double sampleRate);

    std::unique_ptr<AudioFormatReaderSource> currentAudioFileSource;    //reads from the file
    AudioTransportSource audioTransportSource;							//this controls the playback of a positionable audio stream, handling the
																		//starting/stopping and sample-rate conversion
    TimeSliceThread thread;												//thread for the transport source
	std::unique_ptr<ResamplingAudioSource> resamplingAudioSource;		//Resamples the audioTransportSource

	ADSR envelope;
	ADSR::Parameters envParams;

	double levelVal = 0.5;	//Used for level control of individual file players


	int bufferCount;
	float transportEndPosition = audioTransportSource.getLengthInSeconds(); //Used as transport play threshold
};
