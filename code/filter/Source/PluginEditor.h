#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "GUI.h"

class FilterAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, public Timer {
public:
    FilterAudioProcessorEditor (FilterAudioProcessor&);
    ~FilterAudioProcessorEditor();
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void sliderValueChanged (Slider*);
    
private:
    FilterAudioProcessor& processor;
    ScopedPointer<Slider> freqSlider, hiLoSlider, test;
    Image background;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterAudioProcessorEditor)
};

#endif  // PLUGINEDITOR_H_INCLUDED
