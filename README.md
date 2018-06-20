# plugin-suite
Suite of freeware VST/AU plugins: 3-Band Equalizer (EQ3), Delay, Filter, &amp; Flanger) written in C++

### about:
Provided is an open source suite of digital audio processing tools: an EQ3 for attenuating frequencies in three ranges(los/mids/his), a flanger, a simple delay, and a filter that doubles as hi or lo pass. These effects were built atop the JUCE Frameworks, using Xcode & Stanford's Synthesis Toolkit (Lite version 4.5.1). Further, I used photoshop to make the static GUI, worked off of code from my professor [Luke Dahl](https://ccrma.stanford.edu/~lukedahl/) (who provided the Mu45 LFO wavetable and filter coefficient calculations), and used parameter template by [Brian Uosseph](https://github.com/buosseph/juce-audio-plugin-template). _Unfortunately, Steinberg Media Group has decided to kill the VST2 format and effective 2018 this code will no longer compile using their frameworks. The associate .cpp files that pertain to the signal processing may however still be beneficial to others interested in writing their own plugins or performing similar DSP operations_.

### instructions:
Place the *.vst or *.au file in the respective system plugin's folder. The plug-ins should then be accessible to your DAW (digital audio workstation). If your DAW can import plugins from a custom folder, feel free to do so without altering your system plugin folders. If you are looking to work off of the project files, they are set to build for Xcode which means you must be working off a Mac system, however you can easily change the desired IDE in projucer 

### notes:
For more information on the JUCE framework:
https://www.juce.com/features

For more information on the Stanford Synthesis ToolKit:
https://ccrma.stanford.edu/software/stk/

Font "Retro" made by Andre Jotha: 
http://www.dafont.com/retro.font

<img src="https://github.com/marcjones-io/pluginsuite/blob/master/design/screenshots/delay.jpeg" width="200">
<img src="https://github.com/marcjones-io/pluginsuite/blob/master/design/screenshots/filter.jpeg" width="200">
<img src="https://github.com/marcjones-io/pluginsuite/blob/master/design/screenshots/flange.jpeg" width="200">
<img src="https://github.com/marcjones-io/pluginsuite/blob/master/design/screenshots/freeq3.jpg" width="600">
