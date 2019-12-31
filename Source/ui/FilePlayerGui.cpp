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
	
	//setSize(1000, 1000);
}

FilePlayerGui::~FilePlayerGui()
{
    
}

//Component
void FilePlayerGui::resized()
{
	const int NumElements = 3; //How many elements need to be mapped out 
	
	Rectangle<int> area = getLocalBounds(); //Rectangle is used to map out each element of the file player

	int heightPerEl = area.getHeight() / NumElements; 

	Rectangle<int> playButtArea = area.removeFromTop(heightPerEl);
	Rectangle<int> fileChooseArea = area.removeFromTop(heightPerEl);
	Rectangle<int> slider1Area = area.removeFromBottom(heightPerEl);
	
	playButton.setBounds(playButtArea);
    fileChooser->setBounds (fileChooseArea);
	startPosSlider.setBounds(slider1Area);
}

void FilePlayerGui::paint(Graphics& g)
{
	/*Rectangle<int> area = getLocalBounds();
	g.setColour(Colours::aqua);
	g.fillRect(area);*/
}

//Button Listener
void FilePlayerGui::buttonClicked (Button* button)
{
	DBG(startPosSlider.getValue());
	filePlayer->setPosition(startPosSlider.getValue());

    if (filePlayer != nullptr && button == &playButton)
    {
		filePlayer->setPosition(startPosSlider.getValue());
        filePlayer->setPlaying( ! filePlayer->isPlaying());
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
	DBG(startPosSlider.getValue());
	filePlayer->setPosition(startPosSlider.getValue());
}
