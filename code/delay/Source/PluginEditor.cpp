#include "PluginProcessor.h"
#include "PluginEditor.h"


DelayAudioProcessorEditor::DelayAudioProcessorEditor (DelayAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p) {
    time_slider = new Slider ("Time Slider");
    time_slider->setRange (1, 999, 1);
    time_slider->setSliderStyle (Slider::LinearBar);
    time_slider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    time_slider->setColour (Slider::thumbColourId, Colours::white);
    time_slider->setColour (Slider::trackColourId, Colours::white);
    time_slider->setColour (Slider::textBoxTextColourId, Colours::white);
    time_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    time_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x55ffffff));
    time_slider->addListener (this);
    
    feedback_slider = new Slider ("Feedback Slider");
    feedback_slider->setRange (0, 95, 1);
    feedback_slider->setSliderStyle (Slider::LinearBar);
    feedback_slider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    feedback_slider->setColour (Slider::thumbColourId, Colours::white);
    feedback_slider->setColour (Slider::trackColourId, Colours::white);
    feedback_slider->setColour (Slider::textBoxTextColourId, Colours::white);
    feedback_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    feedback_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x55ffffff));
    feedback_slider->addListener (this);
    
    drywet_slider = new Slider ("DryWet Slider");
    drywet_slider->setRange (0, 100, 1);
    drywet_slider->setSliderStyle (Slider::LinearBar);
    drywet_slider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    drywet_slider->setColour (Slider::thumbColourId, Colours::white);
    drywet_slider->setColour (Slider::trackColourId, Colours::white);
    drywet_slider->setColour (Slider::textBoxTextColourId, Colours::white);
    drywet_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    drywet_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x55ffffff));
    drywet_slider->addListener (this);
    
    addAndMakeVisible (time_slider); addAndMakeVisible (feedback_slider); addAndMakeVisible (drywet_slider);

    background = GUI().cachedImage_delay_jpg_1;
    
    setSize (195, 300);
    startTimer(100);
}

DelayAudioProcessorEditor::~DelayAudioProcessorEditor(){
    time_slider = nullptr;
    feedback_slider = nullptr;
    drywet_slider = nullptr;
}

void DelayAudioProcessorEditor::paint (Graphics& g) {
    g.fillAll (Colours::white);
    g.drawImage (background,
                 0, 0, 195, 300,
                 0, 0, background.getWidth(), background.getHeight());
}

void DelayAudioProcessorEditor::resized() {
    time_slider->setBounds (24, 104, 150, 24);
    feedback_slider->setBounds (24, 160, 150, 24);
    drywet_slider->setBounds (24, 224, 150, 24);
}

void DelayAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved) {
    PluginParameter* parameter = nullptr;
    
    if (sliderThatWasMoved == time_slider) {
        parameter = processor.timeParam;
    }
    else if (sliderThatWasMoved == feedback_slider) {
        parameter = processor.fbParam;
    }
    else if (sliderThatWasMoved == drywet_slider) {
        parameter = processor.dryWetParam;
    }
    
    if (parameter != nullptr) {
        parameter->setValueNotifyingHost(parameter->calculateValue(sliderThatWasMoved->getValue()));
    }
}

void DelayAudioProcessorEditor::timerCallback() {
    time_slider->setValue(processor.timeParam->getActualValue(), dontSendNotification);
    feedback_slider->setValue(processor.fbParam->getActualValue(), dontSendNotification);
    drywet_slider->setValue(processor.dryWetParam->getActualValue(), dontSendNotification);
}
