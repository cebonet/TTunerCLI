#include "wavReader.h"
#include "autocorrelation.h"
#include "plotter.h"
#include "peakpicking.h"
#include "recordaudio.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <alsa/asoundlib.h>
#include <unistd.h>
#include <cmath>

#define SAMPLE_RATE 44100
#define WINDOW_SIZE 1024
#define MIN_AMPLITUDE 0.025/2
#define WIN_HAMMING 1
#define WIN_HANN 2
#define WIN_SINE 3

using namespace std;

int main(){
    double last_frequency=0;
    double period; 
    double amplitude;
    double frequency;
    bool audioStatus;
    string MIDI;

    
    // Data buffers
    double* buffer_pcm = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    double* buffer_window = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    double* buffer_acf = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    
    // Instantiate  
    recordaudio audio = recordaudio();
    autocorrelation acf = autocorrelation(WINDOW_SIZE);
    peakpicking pick = peakpicking(WINDOW_SIZE);
    tools tls = tools(WINDOW_SIZE);
    plotter p = plotter();    
   
    // Create window
    acf.window(1, buffer_window);
    
    // Listen and detect 
    do{
        audioStatus = audio.getAudioStream(buffer_pcm);
        acf.autocorrelation_snac(buffer_pcm, buffer_acf);
        period = pick.getPeriod(buffer_acf);
        amplitude = tls.getMaxAmplitude(buffer_acf);
        
        if (amplitude > MIN_AMPLITUDE && period){
            frequency = SAMPLE_RATE/period;
            last_frequency = round(frequency/2);
            MIDI = tls.getMIDI(frequency/2);
            cout  << "\r" << "frequency: " << last_frequency << "  Note:" << MIDI  << flush;
        }else{
            cout  << "\r" << "frequency: " << last_frequency << "  Note:" << MIDI  << flush;
        }
    }
    while (audioStatus);

    audio.closeStream(); 
}


