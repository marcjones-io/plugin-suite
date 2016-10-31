#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Mu45FilterCalc.h"
#include "PluginParameter.h"
#include "BiQuad.h"


class FreeQ3AudioProcessor  : public AudioProcessor {
public:
    //==============================================================================
    FreeQ3AudioProcessor();
    ~FreeQ3AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    PluginParameter *loGain, *midGain, *hiGain;

private:
    stk::BiQuad loFilterL, loFilterR, midFilterL, midFilterR, hiFilterL, hiFilterR;
    void calcParams();
    float fs;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreeQ3AudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
