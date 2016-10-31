#include "PluginProcessor.h"
#include "PluginEditor.h"

//todo
// increase range (down to negative infinity to totally cut) & skew sliders
// improve labels on gui image
// db feedback on sliders
// tighten design overall & stop flickering

FreeQ3AudioProcessorEditor::FreeQ3AudioProcessorEditor (FreeQ3AudioProcessor& p):
AudioProcessorEditor (&p), processor (p) {
    
    addAndMakeVisible(test = new Slider("test"));
    test->setSliderStyle(Slider::LinearBar);
    test->setRange(-30, 30, .1);
    test->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);

    addAndMakeVisible (lo_slider = new Slider ("lo slider"));
    lo_slider->setRange (-15, 6, 0.1);
    lo_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    lo_slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    lo_slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    lo_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    lo_slider->addListener (this);
    
    addAndMakeVisible (mid_slider = new Slider ("mid slider"));
    mid_slider->setRange (-15, 6, 0.1);
    mid_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    mid_slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    mid_slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    mid_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    mid_slider->addListener (this);
    
    addAndMakeVisible (hi_slider = new Slider ("hi slider"));
    hi_slider->setRange (-15, 6, 0.1);
    hi_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    hi_slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    hi_slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    hi_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    hi_slider->addListener (this);
    
    background = GUI().cachedImage_freeq3_jpg_1;
    
    setSize (500, 300);
    startTimer(100);
}

FreeQ3AudioProcessorEditor::~FreeQ3AudioProcessorEditor() {
    lo_slider = nullptr;
    mid_slider = nullptr;
    hi_slider = nullptr;
}

void FreeQ3AudioProcessorEditor::paint (Graphics& g) {
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.drawImage (background,
                 0, 0, 500, 300,
                 0, 0, background.getWidth(), background.getHeight());
}

void FreeQ3AudioProcessorEditor::resized() {
    test->setBounds(300, 50, 100, 30);
    lo_slider->setBounds (40, 104, 100, 100);
    mid_slider->setBounds (200, 104, 100, 100);
    hi_slider->setBounds (352, 104, 100, 100);
}

void FreeQ3AudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved) {
    PluginParameter* parameter = nullptr;
    
    if (sliderThatWasMoved == lo_slider) {
        parameter = processor.loGain;
    }
    else if (sliderThatWasMoved == mid_slider) {
        parameter = processor.midGain;
    }
    else if (sliderThatWasMoved == hi_slider) {
        parameter = processor.hiGain;
    }
    
    if (parameter != nullptr) {
        parameter->setValueNotifyingHost(parameter->calculateValue(sliderThatWasMoved->getValue()));
        
        test->setValue(parameter->getActualValue());
    }
}

void FreeQ3AudioProcessorEditor::timerCallback() {
    lo_slider->setValue(processor.loGain->getActualValue(), dontSendNotification);
    mid_slider->setValue(processor.midGain->getActualValue(), dontSendNotification);
    hi_slider->setValue(processor.hiGain->getActualValue(), dontSendNotification);
}

