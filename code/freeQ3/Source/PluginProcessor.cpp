#include "PluginProcessor.h"
#include "PluginEditor.h"

FreeQ3AudioProcessor::FreeQ3AudioProcessor() {
    hiGain = new PluginParameter("hiGain", 0, -40, 6, "hiGain", "db");
    midGain = new PluginParameter("midGain", 0, -40, 6, "midGain", "db");
    loGain = new PluginParameter("loGain", 0, -40, 6, "loGain", "db");
    addParameter(loGain);    addParameter(midGain);     addParameter(hiGain);
}

FreeQ3AudioProcessor::~FreeQ3AudioProcessor() {
}

const String FreeQ3AudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool FreeQ3AudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FreeQ3AudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FreeQ3AudioProcessor::silenceInProducesSilenceOut() const {
    return false;
}

double FreeQ3AudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int FreeQ3AudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FreeQ3AudioProcessor::getCurrentProgram() {
    return 0;
}

void FreeQ3AudioProcessor::setCurrentProgram (int index) {
}

const String FreeQ3AudioProcessor::getProgramName (int index) {
    return String();
}

void FreeQ3AudioProcessor::changeProgramName (int index, const String& newName) {
}

//==============================================================================
void FreeQ3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    fs = sampleRate;
}

void FreeQ3AudioProcessor::releaseResources() { }

void FreeQ3AudioProcessor::calcParams(){
    float loCoeffs[5];
    Mu45FilterCalc::calcCoeffsLowShelf(loCoeffs, 250, loGain->getActualValue(), fs);
    
    float midCoeffs[5];
    Mu45FilterCalc::calcCoeffsPeak(loCoeffs, 1375, midGain->getActualValue(), .8 /** maybe also .1 **/, fs);
    
    float hiCoeffs[5];
    Mu45FilterCalc::calcCoeffsHighShelf(hiCoeffs, 2500, hiGain->getActualValue(), fs);
   
    loFilterL.setCoefficients(loCoeffs[0], loCoeffs[1], loCoeffs[2], loCoeffs[3], loCoeffs[4]);
    loFilterR.setCoefficients(loCoeffs[0], loCoeffs[1], loCoeffs[2], loCoeffs[3], loCoeffs[4]);
    
    midFilterL.setCoefficients(midCoeffs[0], midCoeffs[1], midCoeffs[2], midCoeffs[3], midCoeffs[4]);
    midFilterR.setCoefficients(midCoeffs[0], midCoeffs[1], midCoeffs[2], midCoeffs[3], midCoeffs[4]);
    
    hiFilterL.setCoefficients(hiCoeffs[0], hiCoeffs[1], hiCoeffs[2], hiCoeffs[3], hiCoeffs[4]);
    hiFilterR.setCoefficients(hiCoeffs[0], hiCoeffs[1], hiCoeffs[2], hiCoeffs[3], hiCoeffs[4]);
}

void FreeQ3AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) {
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    calcParams();
    float* left = buffer.getWritePointer (0);
    float* right = buffer.getWritePointer (1);
    
    for (int samp = 0; samp < buffer.getNumSamples(); samp++) {
        
        left[samp] =  loFilterL.tick(left[samp]);
        right[samp] = loFilterR.tick(right[samp]);
        
        left[samp] = midFilterL.tick(left[samp]);
        right[samp] = midFilterR.tick(right[samp]);
    
        left[samp] =  hiFilterL.tick(left[samp]);
        right[samp] = hiFilterR.tick(right[samp]);
    }
}

bool FreeQ3AudioProcessor::hasEditor() const {
    return true;
}

AudioProcessorEditor* FreeQ3AudioProcessor::createEditor() {
    return new FreeQ3AudioProcessorEditor (*this);
}

void FreeQ3AudioProcessor::getStateInformation (MemoryBlock& destData) { }

void FreeQ3AudioProcessor::setStateInformation (const void* data, int sizeInBytes) { }

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new FreeQ3AudioProcessor();
}
