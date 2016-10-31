#include "PluginProcessor.h"
#include "PluginEditor.h"

FlangeAudioProcessorEditor::FlangeAudioProcessorEditor (FlangeAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p) {
    addAndMakeVisible (time_slider = new Slider ("Time Slider"));
    time_slider->setRange (0.1, 7, .1);
    time_slider->setSliderStyle (Slider::LinearBar);
    time_slider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    time_slider->setColour (Slider::thumbColourId, Colours::white);
    time_slider->setColour (Slider::trackColourId, Colours::white);
    time_slider->setColour (Slider::textBoxTextColourId, Colours::white);
    time_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    time_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x55ffffff));
    time_slider->addListener (this);
    
    addAndMakeVisible (lfo_slider = new Slider ("LFO Slider"));
    lfo_slider->setRange (0.01, 10, .01);
    lfo_slider->setSliderStyle (Slider::LinearBar);
    lfo_slider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    lfo_slider->setColour (Slider::thumbColourId, Colours::white);
    lfo_slider->setColour (Slider::trackColourId, Colours::white);
    lfo_slider->setColour (Slider::textBoxTextColourId, Colours::white);
    lfo_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    lfo_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x55ffffff));
    lfo_slider->addListener (this);
    
    addAndMakeVisible (drywet_slider = new Slider ("DryWet Slider"));
    drywet_slider->setRange (0, 100, 1);
    drywet_slider->setSliderStyle (Slider::LinearBar);
    drywet_slider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    drywet_slider->setColour (Slider::thumbColourId, Colours::white);
    drywet_slider->setColour (Slider::trackColourId, Colours::white);
    drywet_slider->setColour (Slider::textBoxTextColourId, Colours::white);
    drywet_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    drywet_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x55ffffff));
    drywet_slider->addListener (this);
    
    background = GUI().cachedImage_flange_jpg_1;
    
    setSize (195, 300);
    startTimer(100);
}

FlangeAudioProcessorEditor::~FlangeAudioProcessorEditor() {
}

void FlangeAudioProcessorEditor::paint (Graphics& g) {
    g.fillAll (Colours::white);
    g.drawImage (background,
                 0, 0, 195, 300,
                 0, 0, background.getWidth(), background.getHeight());
}

void FlangeAudioProcessorEditor::resized() {
    time_slider->setBounds (24, 104, 150, 24);
    lfo_slider->setBounds (24, 160, 150, 24);
    drywet_slider->setBounds (24, 224, 150, 24);
}

void FlangeAudioProcessorEditor::sliderValueChanged (Slider* slider) {
    PluginParameter* parameter = nullptr;
    
    if (slider == time_slider) {
        parameter = processor.delayParam;
    }
    else if (slider == lfo_slider) {
        parameter = processor.lfoFreqParam;
    }
    else if (slider == drywet_slider) {
        parameter = processor.dryWetParam;
    }
    
    if (parameter != nullptr) {
        parameter->setValueNotifyingHost(parameter->calculateValue(slider->getValue()));
    }
}

void FlangeAudioProcessorEditor::timerCallback() {
    time_slider->setValue(processor.delayParam->getActualValue(), dontSendNotification);
    lfo_slider->setValue(processor.lfoFreqParam->getActualValue(), dontSendNotification);
    drywet_slider->setValue(processor.dryWetParam->getActualValue(), dontSendNotification);
}
