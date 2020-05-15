# Plugin

This repo contains simple Reverb, Delay and Distortion VST3 plugins made in c++ and JUCE.
Also included are a simple audio player plugin which can play WAV or MP3 files, and the JUCE plugin host for testing all the plugins.

To set up the plugins and the plugin host, do the following:

1. open the plugin host executable and go to Options > Edit the list of available plug-ins
2. In the available plugins list, go to Options > Scan for new or updated VST3 plug-ins and select the folder with the VST3 files
3. On the main screen, right-click and go to "yourcompany" tab and select the audio player plugin and the desired effect plugin.
4. Connect the output channels of the audio player (lower dots) to the input channels of the effect plugin, and the output channels of the effect plugin to the audio output
