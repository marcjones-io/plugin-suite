#ifndef __JUCE_HEADER_1B5DFE0B2C44A6__
#define __JUCE_HEADER_1B5DFE0B2C44A6__

#include "JuceHeader.h"

class GUI  : public Component, public SliderListener {
public:
    GUI ();
    ~GUI();
    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);

    // Binary resources:
    static const char* filter_jpg;
    static const int filter_jpgSize;
    Image cachedImage_filter_jpg_1;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1B5DFE0B2C44A6__
