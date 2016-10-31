#ifndef __JUCE_HEADER_1B5DFE0B2C44A6__
#define __JUCE_HEADER_1B5DFE0B2C44A6__
#include "JuceHeader.h"

class GUI  : public Component {
public:
    GUI ();
    ~GUI();

    // Binary resources:
    static const char* freeq3_jpg;
    static const int freeq3_jpgSize;
    Image cachedImage_freeq3_jpg_1;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1B5DFE0B2C44A6__
