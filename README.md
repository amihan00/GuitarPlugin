# TEMPEST vst3 audio plugin

This repo contains a vst3 audio plugin with the effects of distortion, delay and reverb, made in C++ and using JUCE framework.


![image](https://user-images.githubusercontent.com/22690754/111075770-cdcde000-84e9-11eb-8341-c3dc759b48c3.png)


## Setup

If on MacOS, copy the vst3 file to:
Library/Audio/Plug-ins/VST3

If on Windows, copy the vst3 file to:
C:\Program Files\Common Files\VST3

## Effect variables
All effects have a dry/wet mixer control called Mix, and can be turned on or off by the button at the bottom of that effect.

### Distortion
- Tone - signal tone, eliminates lower frequencies
- Gain - signal gain, amplifies the signal and enables more distortion
- Clip buttons - enables soft or hard clipping distortion

### Delay
- Time - time between delayed signals, up to 2 seconds
- Feedback - attenuation of the delayed signals

### Reverb
- Room size - duration of the sound reverberation
- Damping - Attenuation of the higher frequencies
- Width - stereo offset


The delay effect is based on the ffTapeDelay by Daniel Walz: https://github.com/ffAudio/ffTapeDelay
