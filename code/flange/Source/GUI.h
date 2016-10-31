#ifndef __JUCE_HEADER_1B5DFE0B2C44A6__
#define __JUCE_HEADER_1B5DFE0B2C44A6__

#include "JuceHeader.h"

class GUI  : public Component {
public:
    GUI ();
    ~GUI();
    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);

    // Binary resources:
    static const char* flange_jpg;
    static const int flange_jpgSize;
    Image cachedImage_flange_jpg_1;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUI)
};

#endif   // __JUCE_HEADER_1B5DFE0B2C44A6__
