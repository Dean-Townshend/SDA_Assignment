#include "FilePlayerGui.h"

FilePlayerGui::FilePlayerGui()
{
    playButton.addListener (this);
    addAndMakeVisible (playButton);
    
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

	//The slider
	addAndMakeVisible(slider1);
	slider1.setSliderStyle(Slider::LinearHorizontal);
	slider1.setColour(Slider::thumbColourId, Colours::red);


	//setSize(1000, 1000);
}

FilePlayerGui::~FilePlayerGui()
{
    
}

//Component
void FilePlayerGui::resized()
{
	const int NumElements = 3; 
	
	Rectangle<int> area = getLocalBounds(); //

	int heightPerEl = area.getHeight() / NumElements;

	Rectangle<int> playButtArea = area.removeFromTop(heightPerEl);
	Rectangle<int> fileChooseArea = area.removeFromTop(heightPerEl);
	Rectangle<int> slider1Area = area.removeFromBottom(heightPerEl);

	
	
	playButton.setBounds(playButtArea);
    fileChooser->setBounds (fileChooseArea);
	slider1.setBounds(slider1Area);
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
    if (filePlayer != nullptr && button == &playButton)
    {
        filePlayer->setPlaying( ! filePlayer->isPlaying());
    }
}

//Slider Listener
void FilePlayerGui::sliderValueChanged(Slider* slider)
{
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
