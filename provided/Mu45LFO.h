//
//  Mu45LFO.h
//  mu45-LD-P04-FlangeMod
//
//  Created by lsd5k on 3/4/15.
//
//

#ifndef __mu45_LD_P04_FlangeMod__Mu45LFO__
#define __mu45_LD_P04_FlangeMod__Mu45LFO__

#include <stdio.h>

#endif /* defined(__mu45_LD_P04_FlangeMod__Mu45LFO__) */

class Mu45LFO {
public:
    Mu45LFO();
    void setFreq(float freq, float fs);
    float tick();
    void resetPhase();
    float output(float phase_offfset);
    
private:
    static const int N = 1024;      // size of the wavetable
    float table[N];                 // the wavetable
    float phase_inc;                // amount to increment phase each tick
    float phase;                    // current index into the wavetable
};