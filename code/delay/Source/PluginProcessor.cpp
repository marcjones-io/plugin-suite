#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DelayAudioProcessor::DelayAudioProcessor() {
    dryWetParam = new PluginParameter("wetDry", 0, 0, 100, "wet_dry_pct", "%");
    fbParam = new PluginParameter("feedback", 0, 0, 95, "feedback_pct", "%");
    timeParam = new PluginParameter("delayTime", 1, 1, 999, "delayTimeInMS", "ms");
    addParameter(dryWetParam); addParameter(fbParam); addParameter(timeParam);
}

DelayAudioProcessor::~DelayAudioProcessor() {
    dryWetParam = nullptr;
    fbParam = nullptr;
    timeParam = nullptr;
}

//==============================================================================
const String DelayAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool DelayAudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DelayAudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DelayAudioProcessor::silenceInProducesSilenceOut() const {
    return false;
}

double DelayAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int DelayAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DelayAudioProcessor::getCurrentProgram() {
    return 0;
}

void DelayAudioProcessor::setCurrentProgram (int index) {
}

const String DelayAudioProcessor::getProgramName (int index) {
    return String();
}

void DelayAudioProcessor::changeProgramName (int index, const String& newName) {
}

//==============================================================================
void DelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    fs = sampleRate;
    fb=0;
    dryGain = 1; wetGain = 0;
    int s = calcSampsFromMS(999);
    leftDelayLine.setMaximumDelay(s); //why do this try that
    rightDelayLine.setMaximumDelay(s);
}

void DelayAudioProcessor::releaseResources() {
    dryWetParam = nullptr;
    fbParam = nullptr;
    timeParam = nullptr;
}

int DelayAudioProcessor::calcSampsFromMS(int ms) {
    return ms/1000*fs;
}

void DelayAudioProcessor::calcParams(){
    fb = .01*fbParam->getActualValue();
    wetGain = .01*dryWetParam->getActualValue();
    int delaytime = timeParam->getActualValue();
    leftDelayLine.setDelay(calcSampsFromMS(delaytime));
    rightDelayLine.setDelay(calcSampsFromMS(delaytime));
}

void DelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) {
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    calcParams();
    float* left = buffer.getWritePointer (0);
    float* right = buffer.getWritePointer (1);
    
    for (int samp = 0; samp < buffer.getNumSamples(); samp++) {
        tempOutL = leftDelayLine.nextOut();
        tempOutR = rightDelayLine.nextOut();
        
        leftDelayLine.tick(wetGain * left[samp] + fb * tempOutL);
        rightDelayLine.tick(wetGain * right[samp] + fb * tempOutR);
        
        left[samp] = (dryGain * left[samp]) + (wetGain  * tempOutL);
        right[samp] = (dryGain * right[samp]) + (wetGain * tempOutR);
    }
}

//==============================================================================
bool DelayAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DelayAudioProcessor::createEditor() {
    return new DelayAudioProcessorEditor (*this);
}

//==============================================================================
void DelayAudioProcessor::getStateInformation (MemoryBlock& destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new DelayAudioProcessor();
}
