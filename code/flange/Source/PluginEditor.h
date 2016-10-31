#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "GUI.h"

class FlangeAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, public Timer {
public:
    FlangeAudioProcessorEditor (FlangeAudioProcessor&);
    ~FlangeAudioProcessorEditor();
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void sliderValueChanged (Slider*);

private:
    FlangeAudioProcessor& processor;
    ScopedPointer<Slider> time_slider, lfo_slider, drywet_slider;
    Image background;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangeAudioProcessorEditor)
};

#endif // PLUGINEDITOR_H_INCLUDED
