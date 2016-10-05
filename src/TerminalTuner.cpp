#include "wavReader.h"
#include "autocorrelation.h"
#include "plotter.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define WINDOW_SIZE 1024 
#define SOUND_PATH soundSamples

using namespace std;

int main(){
    plotter p = plotter();    
    wavReader r = wavReader("soundSamples/329.628.wav", WINDOW_SIZE);
    autocorrelation acf = autocorrelation(WINDOW_SIZE);


    short* buffer = (short*) malloc(sizeof(short)*WINDOW_SIZE);
    float* buffer_acf = (float*) malloc(sizeof(float)*WINDOW_SIZE);
    float* buffer_acf2 = (float*) malloc(sizeof(float)*WINDOW_SIZE);
    
    r.getWavBuffer(buffer);
    acf.autocorrelation_acf(buffer, buffer_acf);
    acf.autocorrelation_nacf2(buffer, buffer_acf2);

    p.write1DPlotData("plots/wav.dat", buffer, WINDOW_SIZE);
    p.write1DPlotData("plots/acf.dat", buffer_acf, WINDOW_SIZE);
    p.write1DPlotData("plots/nacf2.dat", buffer_acf2, WINDOW_SIZE);


    exit(0);
}
