#include "wavReader.h"
#include "autocorrelation.h"
#include "plotter.h"
#include "peakpicking.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#define WINDOW_SIZE 1024
#define WIN_HAMMING 1
#define WIN_HANN 2
#define WIN_SINE 3

using namespace std;

int main(){
    wavReader r = wavReader("soundSamples/329.628.wav", WINDOW_SIZE);
    autocorrelation acf = autocorrelation(WINDOW_SIZE);
    

    // Data buffers
    short* buffer = (short*) malloc(sizeof(short)*WINDOW_SIZE);
    double* buffer_snac = (double*) malloc(sizeof(double)*WINDOW_SIZE);
   
    // Autocorrelation functions
    int sr = r.getWavBuffer(buffer);
    acf.autocorrelation_snac(buffer, buffer_snac);

    // Peak Picking
    peakpicking pick = peakpicking(buffer_snac, WINDOW_SIZE);
    double period = pick.getPeriod();
    cout << "Period: " << period << endl;
    cout << "frequency: " << sr/period << endl;

    
    exit(0);
}
