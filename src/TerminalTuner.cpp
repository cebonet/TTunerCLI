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

#define SAMPLE_RATE 44100
#define WINDOW_SIZE 1024
#define MIN_AMPLITUDE 0.025
#define WIN_HAMMING 1
#define WIN_HANN 2
#define WIN_SINE 3

using namespace std;

int main(){
    double last_frequency=0;
    double period; 
    
    // Data buffers
    double* buffer = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    double* buffer_window = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    double* buffer_snac = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    
    // Instantiate  
    recordaudio audio = recordaudio();
    autocorrelation acf = autocorrelation(WINDOW_SIZE);
    peakpicking pick = peakpicking(buffer_snac, WINDOW_SIZE);
    tools tls = tools(buffer_snac, WINDOW_SIZE);
    plotter p = plotter();    
   
    // Create window
    acf.window(WIN_SINE, buffer_window);
    
    bool audioStatus = true;
    while (audioStatus){
        audioStatus = audio.getAudioStream(buffer);
         

        // Autocorrelation functions
        acf.autocorrelation_snac(buffer, buffer_snac);

        // Peak Picking
        period = pick.getPeriod();

        // Print f(0)
        if (tls.getMaxAmplitude() > MIN_AMPLITUDE && period){
            last_frequency = SAMPLE_RATE/period;
            cout   << "frequency: " << tls.getMaxAmplitude() << "  " << endl;
        }else{
            cout  << "frequency: " << last_frequency << "  "  << endl;
        }
    }
    audio.closeStream(); 
}


