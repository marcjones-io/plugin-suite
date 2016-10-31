#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginParameter.h"
#include "DelayL.h"
#include "MU45LFO.h"

class FlangeAudioProcessor  : public AudioProcessor {
public:
    FlangeAudioProcessor();
    ~FlangeAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    PluginParameter *dryWetParam, *lfoFreqParam, *delayParam;
    Mu45LFO myLFO;
    float lfovalu, dryGain, wetGain, lfoFreq, delayTime;
    int ctrlNum=50, ctrlCtr=0;

private:
    
    stk::DelayL rightDelayLine, leftDelayLine;
    float fs;
    void calcParams();
    int calcSampsFromMS(int ms);
    void calcDelays();
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangeAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
