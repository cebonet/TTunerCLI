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



    // Plots
    short* buffer = (short*) malloc(sizeof(short)*WINDOW_SIZE);
    float* buffer_window = (float*) malloc(sizeof(float)*WINDOW_SIZE);
    float* buffer_acf = (float*) malloc(sizeof(float)*WINDOW_SIZE);
    float* buffer_acf2 = (float*) malloc(sizeof(float)*WINDOW_SIZE);
    float* buffer_nacf2 = (float*) malloc(sizeof(float)*WINDOW_SIZE);
    float* buffer_acf2_win = (float*) malloc(sizeof(float)*WINDOW_SIZE);
    float* buffer_snac = (float*) malloc(sizeof(float)*WINDOW_SIZE);
    float* buffer_wsnac = (float*) malloc(sizeof(float)*WINDOW_SIZE);
    
    r.getWavBuffer(buffer);
    acf.window(2, buffer_window);
    acf.autocorrelation_acf(buffer, buffer_acf);
    acf.autocorrelation_acf2(buffer, buffer_acf2);
    acf.autocorrelation_nacf2(buffer, buffer_nacf2);
    acf.autocorrelation_acf2_win(buffer, buffer_acf2_win);
    acf.autocorrelation_snac(buffer, buffer_snac);
    acf.autocorrelation_wsnac(buffer, buffer_snac);

    p.write1DPlotData("plots/wav.dat", buffer, WINDOW_SIZE);
    p.write1DPlotData("plots/acf.dat", buffer_acf, WINDOW_SIZE);
    p.write1DPlotData("plots/acf2.dat", buffer_acf2, WINDOW_SIZE);
    p.write1DPlotData("plots/nacf2.dat", buffer_nacf2, WINDOW_SIZE);
    p.write1DPlotData("plots/acf2_win.dat", buffer_acf2_win, WINDOW_SIZE);
    p.write1DPlotData("plots/snac.dat", buffer_snac, WINDOW_SIZE);
    p.write1DPlotData("plots/window.dat", buffer_window, WINDOW_SIZE);


    exit(0);
}
