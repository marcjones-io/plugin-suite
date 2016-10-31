#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "GUI.h"

class FreeQ3AudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, public Timer {
public:
    FreeQ3AudioProcessorEditor (FreeQ3AudioProcessor&);
    ~FreeQ3AudioProcessorEditor();
    void timerCallback() override;
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void paint (Graphics&) override;
    void resized() override;

private:
    FreeQ3AudioProcessor& processor;
    ScopedPointer<Slider> lo_slider;
    ScopedPointer<Slider> mid_slider;
    ScopedPointer<Slider> hi_slider;

    Image background;
    
    ScopedPointer<Slider> test;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreeQ3AudioProcessorEditor)
};
#endif
