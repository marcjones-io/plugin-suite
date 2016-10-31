#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "GUI.h"

class DelayAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, public Timer {
public:
    DelayAudioProcessorEditor (DelayAudioProcessor&);
    ~DelayAudioProcessorEditor();
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void sliderValueChanged (Slider*);
    
private:
    DelayAudioProcessor& processor;
    ScopedPointer<Slider> time_slider;
    ScopedPointer<Slider> feedback_slider;
    ScopedPointer<Slider> drywet_slider;
    Image background;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
