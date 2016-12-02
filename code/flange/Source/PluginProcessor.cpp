#include "PluginProcessor.h"
#include "PluginEditor.h"

//todo audio out unaffected

FlangeAudioProcessor::FlangeAudioProcessor() {
    dryWetParam = new PluginParameter("dryWetParam", 0, 0, 100, "dryWetParam", "%");
    lfoFreqParam = new PluginParameter("lfoFreqParam", .11, 0.01, 10, "lfoFreqParam", "");
    delayParam = new PluginParameter("delayParam", 2.5, 0.1, 7, "delayParam", "");
    addParameter(dryWetParam); addParameter(lfoFreqParam); addParameter(delayParam);
}

FlangeAudioProcessor::~FlangeAudioProcessor() {
}

const String FlangeAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool FlangeAudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FlangeAudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FlangeAudioProcessor::silenceInProducesSilenceOut() const {
    return false;
}

double FlangeAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int FlangeAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FlangeAudioProcessor::getCurrentProgram() {
    return 0;
}

void FlangeAudioProcessor::setCurrentProgram (int index) {
}

const String FlangeAudioProcessor::getProgramName (int index) {
    return String();
}

void FlangeAudioProcessor::changeProgramName (int index, const String& newName) {
}


int FlangeAudioProcessor::calcSampsFromMS(float ms) {
    return ms/1000*fs;
}

void FlangeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    fs = sampleRate;
    int samples = calcSampsFromMS(delayParam->getActualMaximum());
    rightDelayLine.setMaximumDelay(samples);
    leftDelayLine.setMaximumDelay(samples);
    calcParams();
}


void FlangeAudioProcessor::calcParams()    {
    myLFO.setFreq(lfoFreqParam->getActualValue(), fs/ctrlNum);
    
    wetGain = 0.01 * dryWetParam->getActualValue();
    dryGain = 1-wetGain;
}

void FlangeAudioProcessor::releaseResources() { 
}

void FlangeAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) {
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
    
    float* left = buffer.getWritePointer (0);
    float* right = buffer.getWritePointer (1);
    calcParams();
    
    for (int samp = 0; samp < buffer.getNumSamples(); samp++)     {
        if (ctrlCtr%ctrlNum==0){
            lfovalu = myLFO.tick();
            lfovalu = (lfovalu+1)/2; //normalize to 0-1 range from -1-1
            
            int samples = calcSampsFromMS(delayParam->getActualValue() * lfovalu);
            rightDelayLine.setDelay(samples);
            leftDelayLine.setDelay(samples);
            ctrlCtr = 0;
        }
        left[samp] = dryGain * left[samp] + wetGain * leftDelayLine.tick(left[samp]);
        right[samp] = dryGain * right[samp] + wetGain * rightDelayLine.tick(right[samp]);
        ctrlCtr++;
    }
}

bool FlangeAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FlangeAudioProcessor::createEditor() {
    return new FlangeAudioProcessorEditor (*this);
}

void FlangeAudioProcessor::getStateInformation (MemoryBlock& destData) {
}

void FlangeAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new FlangeAudioProcessor();
}
