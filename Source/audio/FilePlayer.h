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
    void releaseResources() override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;

	void setPosition(double newPosition);

	void setEndPosition(double endPosition);

	double getPosition();

	double getEndPosition();

	double getLength();

	void setPlaybackRate(double newRate);

	void setLevel(double levelSliderval);

private:

	void setAdsrSampleRate(double sampleRate);

    std::unique_ptr<AudioFormatReaderSource> currentAudioFileSource;    //reads from the file
    AudioTransportSource audioTransportSource;	        // this controls the playback of a positionable audio stream, handling the
                                                        // starting/stopping and sample-rate conversion
    TimeSliceThread thread;                             //thread for the transport source
	std::unique_ptr<ResamplingAudioSource> resamplingAudioSource;

	ADSR envelope;
	ADSR::Parameters envParams;

	double levelVal = 0.5;

	float transportEndPosition = audioTransportSource.getLengthInSeconds();
};
