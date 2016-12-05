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
#define MIN_AMPLITUDE 0.025
#define WIN_HAMMING 1
#define WIN_HANN 2
#define WIN_SINE 3

using namespace std;

int main (int argc, char *argv[]){

    std::cout << argv[0] << std::endl;

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
    recordaudio audio = recordaudio(true);
    bool streamValid = audio.openStream();
    autocorrelation acf = autocorrelation(WINDOW_SIZE);
    peakpicking pick = peakpicking(WINDOW_SIZE);
    tools tls = tools(WINDOW_SIZE);
    plotter p = plotter();    
   
    // Create window - currently not used
    acf.window(1, buffer_window);
    
    // Listen and detect 
    do{
        audioStatus = audio.getAudioStream(buffer_pcm);
        acf.autocorrelation_snac(buffer_pcm, buffer_acf);
        period = pick.getPeriod(buffer_acf);
        amplitude = tls.getMaxAmplitude(buffer_acf);
        
        if (amplitude > MIN_AMPLITUDE && period){
            // The second peak is always the right one, but why?
            // this can however be solved by dividing by 2 - shifts it to second peak
            frequency = SAMPLE_RATE/period/2; 
            last_frequency = frequency;
            MIDI = tls.getMIDI(frequency);
            cout  << "\r" << "frequency: " << last_frequency << "  Note:" << MIDI  << flush;
            if (frequency > 300 && frequency < 333){
                p.write1DPlotData("plots/snac.dat", buffer_acf, WINDOW_SIZE);
                cout << "Plot written!" << endl;
            }
        }else{
            cout  << "\r" << "frequency: " << last_frequency << "  Note:" << MIDI  << flush;
        }
    }
    while (audioStatus && streamValid);

    audio.closeStream(); 
}


