/*
  ==============================================================================
    FilePlayerGui.h
  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../audio/FilePlayer.h"

/** Gui for the FilePlayer class */
class FilePlayerGui :   public  Component,
                        private Button::Listener,
                        private FilenameComponentListener,
						private Slider::Listener 
{
public:
    /** constructor - receives a reference to a FilePlayer object to control */
    FilePlayerGui();
    
    /** Destructor */
    ~FilePlayerGui();
    
    /** sets the file player that this gui controls */
    void setFilePlayer (FilePlayer* fp);
    
    //Component
    void resized() override;

	void paint(Graphics& g) override;

private:
    //Button Listener
    void buttonClicked (Button* button) override;

	//Slider Listener
	void sliderValueChanged (Slider* slider) override;
    
    //FilenameComponentListener
    void filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged) override;
    
    TextButton playButton {">"};
    std::unique_ptr<FilenameComponent> fileChooser;
    
    FilePlayer* filePlayer {nullptr};

	Slider slider1;
};
