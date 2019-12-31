#include "FilePlayerGui.h"

FilePlayerGui::FilePlayerGui()
{
	//Button
    playButton.addListener (this);
    addAndMakeVisible (playButton);
    
	//File Chooser
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    fileChooser = std::make_unique<FilenameComponent> ("audiofile",
                                                       File(),
                                                       true, false, false,
                                                       formatManager.getWildcardForAllFormats(),
                                                       String(),
                                                       "(select an audio file)");
    fileChooser->addListener (this);
    addAndMakeVisible (fileChooser.get());

	//Start slider
	startPosSlider.addListener(this);
	addAndMakeVisible(startPosSlider);
	startPosSlider.setSliderStyle(Slider::LinearHorizontal);
	startPosSlider.setColour(Slider::thumbColourId, Colours::red);
	startPosSlider.setRange(0.0, 1.0);

	//Pitch slider
	pitchSlider.addListener(this);
	addAndMakeVisible(pitchSlider);
	pitchSlider.setSliderStyle(Slider::LinearHorizontal);
	pitchSlider.setColour(Slider::thumbColourId, Colours::blue);
	pitchSlider.setRange(0.1, 5.0);
	pitchSlider.setValue(0.1);
	
	//setSize(1000, 1000);
}

FilePlayerGui::~FilePlayerGui()
{
    
}

//Component
void FilePlayerGui::resized()
{
	const int NumElements = 4; //How many elements need to be mapped out 
	
	Rectangle<int> area = getLocalBounds(); //Rectangle is used to map out each element of the file player

	int heightPerEl = area.getHeight() / NumElements; 

	Rectangle<int> playButtArea = area.removeFromTop(heightPerEl);
	Rectangle<int> fileChooseArea = area.removeFromTop(heightPerEl);
	Rectangle<int> startSliderArea = area.removeFromBottom(heightPerEl);
	Rectangle<int> pitchSliderArea = area.removeFromTop(heightPerEl);
	
	playButton.setBounds(playButtArea);
    fileChooser->setBounds (fileChooseArea);
	startPosSlider.setBounds(startSliderArea);
	pitchSlider.setBounds(pitchSliderArea);
}

void FilePlayerGui::paint(Graphics& g)
{

}

//Button Listener
void FilePlayerGui::buttonClicked (Button* button)
{
	//DBG(startPosSlider.getValue());
    if (filePlayer != nullptr && button == &playButton)
    {
        filePlayer->setPlaying( ! filePlayer->isPlaying());
		filePlayer->setPosition(startPosSlider.getValue());
    }
}

void FilePlayerGui::setFilePlayer (FilePlayer* fp)
{
    filePlayer = fp;
}

//FilenameComponentListener
void FilePlayerGui::filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged)
{
    if (fileComponentThatHasChanged == fileChooser.get())
    {
        File audioFile (fileChooser->getCurrentFile().getFullPathName());
        
        if(filePlayer != nullptr && audioFile.existsAsFile())
        {
            filePlayer->loadFile(audioFile);
        }
        else
        {
            AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                         "sdaTransport",
                                         "Couldn't open file!\n\n");
        }
    }
}

//Slider Listener
void FilePlayerGui::sliderValueChanged(Slider* slider)
{
	if (slider == &startPosSlider)
	{
		DBG(startPosSlider.getValue());
		filePlayer->setPosition(startPosSlider.getValue());
	}
	if (slider == &pitchSlider)
	{
		DBG(pitchSlider.getValue());
		filePlayer->setPlaybackRate(pitchSlider.getValue());
	}
}
