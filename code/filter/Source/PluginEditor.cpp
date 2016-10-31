#include "PluginProcessor.h"
#include "PluginEditor.h"

FilterAudioProcessorEditor::FilterAudioProcessorEditor (FilterAudioProcessor& p) : AudioProcessorEditor (&p), processor (p) {
    
    addAndMakeVisible (hiLoSlider = new Slider ("Hi/Lo Slider"));
    hiLoSlider->setRange (0, 1, 1);
    hiLoSlider->setSliderStyle (Slider::LinearHorizontal);
    hiLoSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    hiLoSlider->setColour (Slider::thumbColourId, Colour (0xffe9e9e9));
    hiLoSlider->setColour (Slider::trackColourId, Colour (0x34ffffff));
    hiLoSlider->addListener (this);

    addAndMakeVisible (freqSlider = new Slider ("Freq Slider"));
    freqSlider->setRange (0, 22000, 1);
    freqSlider->setSliderStyle (Slider::Rotary);
    freqSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    freqSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    freqSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    freqSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    freqSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    freqSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    freqSlider->addListener (this);

    background = GUI().cachedImage_filter_jpg_1;

    setSize(195,300);
    startTimer(100);
}

FilterAudioProcessorEditor::~FilterAudioProcessorEditor() {
    hiLoSlider = nullptr;
    freqSlider = nullptr;
}

void FilterAudioProcessorEditor::paint (Graphics& g) {
    g.fillAll (Colours::white);
    g.setColour(Colours::black);
    g.drawImage (background,
                 0, 0, 195, 300,
                 0, 0, background.getWidth(), background.getHeight());
}

void FilterAudioProcessorEditor::resized() {
    hiLoSlider->setBounds (48, 216, 96, 16);
    freqSlider->setBounds (16, 88, 150, 120);
}

void FilterAudioProcessorEditor::sliderValueChanged(Slider* slider)     {
    PluginParameter* parameter = nullptr;
    if (slider == freqSlider) {
        parameter = processor.freqParam;
    } else if (slider == hiLoSlider) {
        parameter = processor.hiLoParam;
    }
    
    if (parameter != nullptr) {
        parameter->setValueNotifyingHost(parameter->calculateValue(slider->getValue()));
    }
}

void FilterAudioProcessorEditor::timerCallback()    {
    hiLoSlider->setValue(processor.hiLoParam->getActualValue(), dontSendNotification);
    freqSlider->setValue(processor.freqParam->getActualValue(), dontSendNotification);
}

