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
#include <iomanip>

#define SAMPLE_RATE 44100
#define WINDOW_SIZE 1024
#define MIN_AMPLITUDE 4.5961e-13
#define WIN_HAMMING 1
#define WIN_HANN 2
#define WIN_SINE 3

using namespace std;

int main (int argc, char *argv[]){

    std::cout << argv[0] << std::endl;

    double last_frequency=0;
    double period; 
    double amplitude;
    double frequency = 0;
    double targetFrequency = 0;
    bool audioStatus;
    int MIDInumber = 0;
    string MIDInote;

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
        amplitude = tls.getMaxAmplitude(buffer_pcm);
        //cout << amplitude << endl;
        
        if (amplitude > MIN_AMPLITUDE){
            // The second peak is always the right one, but why?
            // this can however be solved by dividing by 2 - shifts it to second peak
            acf.autocorrelation_snac(buffer_pcm, buffer_acf);
            period = pick.getPeriod(buffer_acf);
            if (period){
                frequency = SAMPLE_RATE/period/2; 
                MIDInumber = tls.getMIDI(frequency);
                MIDInote = tls.getMIDIasNote(frequency);
                targetFrequency = tls.noteToFrequency(MIDInumber); 
            }
        }
        cout  
            << setprecision(5) << "\r" 
            << "Note:" << MIDInote << "  " << frequency << "Hz / " << targetFrequency << "Hz"
            <<  flush;
    }
    while (audioStatus && streamValid);

    audio.closeStream(); 
}


