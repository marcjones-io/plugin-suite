#include "PluginProcessor.h"
#include "PluginEditor.h"

//pop needs fixing .. maybe change lower/upper range of freq param

FilterAudioProcessor::FilterAudioProcessor() {
    hiLoParam = new PluginParameter("hi/lo", 0, 0, 1, "hi/lo", "");
    freqParam = new PluginParameter("freq", 0, 0, 22000, "freq", "hz");
    addParameter(freqParam);     addParameter(hiLoParam);
}

FilterAudioProcessor::~FilterAudioProcessor() {
}

const String FilterAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool FilterAudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FilterAudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FilterAudioProcessor::silenceInProducesSilenceOut() const {
    return false;
}

double FilterAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int FilterAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FilterAudioProcessor::getCurrentProgram() {
    return 0;
}

void FilterAudioProcessor::setCurrentProgram (int index) {
}

const String FilterAudioProcessor::getProgramName (int index) {
    return String();
}

void FilterAudioProcessor::changeProgramName (int index, const String& newName) {
}

void FilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    fs = sampleRate;
}

void FilterAudioProcessor::releaseResources() {
}

void FilterAudioProcessor::calcParams() {
    float loCoeffs[5], hiCoeffs[5];
    
    Mu45FilterCalc::calcCoeffsLPF(loCoeffs, freqParam->getActualValue(), .8, fs);
    Mu45FilterCalc::calcCoeffsHPF(hiCoeffs, freqParam->getActualValue(), .8, fs);
    
    loFilterL.setCoefficients(loCoeffs[0], loCoeffs[1], loCoeffs[2], loCoeffs[3], loCoeffs[4]);
    loFilterR.setCoefficients(loCoeffs[0], loCoeffs[1], loCoeffs[2], loCoeffs[3], loCoeffs[4]);
    
    hiFilterL.setCoefficients(hiCoeffs[0], hiCoeffs[1], hiCoeffs[2], hiCoeffs[3], hiCoeffs[4]);
    hiFilterR.setCoefficients(hiCoeffs[0], hiCoeffs[1], hiCoeffs[2], hiCoeffs[3], hiCoeffs[4]);
}

void FilterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) {
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    calcParams();
    float* left = buffer.getWritePointer (0);
    float* right = buffer.getWritePointer (1);
    
    for (int samp = 0; samp < buffer.getNumSamples(); samp++) {
    
        if( hiLoParam->getActualValue() == 0) {
            left[samp] =  hiFilterL.tick(left[samp]);
            right[samp] =  hiFilterR.tick(right[samp]);
        }
        else {
            left[samp] =  loFilterL.tick(left[samp]);
            right[samp] = loFilterR.tick(right[samp]);
        }
    }
}

bool FilterAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FilterAudioProcessor::createEditor() {
    return new FilterAudioProcessorEditor (*this);
}

void FilterAudioProcessor::getStateInformation (MemoryBlock& destData) {
}

void FilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new FilterAudioProcessor();
}
