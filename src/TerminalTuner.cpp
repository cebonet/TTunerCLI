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
    plotter p = plotter();    
    wavReader r = wavReader("soundSamples/329.628.wav", WINDOW_SIZE);
    autocorrelation acf = autocorrelation(WINDOW_SIZE);
    


    // Data buffers
    short* buffer = (short*) malloc(sizeof(short)*WINDOW_SIZE);
    double* buffer_window = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    double* buffer_acf = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    double* buffer_acf2 = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    double* buffer_nacf2 = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    double* buffer_acf2_win = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    double* buffer_snac = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    double* buffer_wsnac = (double*) malloc(sizeof(double)*WINDOW_SIZE);
   
    // Autocorrelation functions
    int sr = r.getWavBuffer(buffer);
    acf.window(WIN_HANN, buffer_window);
    acf.autocorrelation_acf(buffer, buffer_acf);
    acf.autocorrelation_acf2(buffer, buffer_acf2);
    acf.autocorrelation_nacf2(buffer, buffer_nacf2);
    acf.autocorrelation_acf2_win(buffer, buffer_acf2_win);
    acf.autocorrelation_snac(buffer, buffer_snac);
    acf.autocorrelation_wsnac(buffer, WIN_HANN , buffer_wsnac);

    // Peak Picking
    peakpicking pick = peakpicking(buffer_snac, WINDOW_SIZE);
    double period = pick.getPeriod();
    cout << "Period: " << period << endl;
    cout << "frequency: " << sr/period << endl;


    
    // Plots
    p.write1DPlotData("plots/wav.dat", buffer, WINDOW_SIZE);
    p.write1DPlotData("plots/window.dat", buffer_window, WINDOW_SIZE);
   
    p.write1DPlotData("plots/acf.dat", buffer_acf, WINDOW_SIZE);
    p.write1DPlotData("plots/acf2.dat", buffer_acf2, WINDOW_SIZE);
    p.write1DPlotData("plots/nacf2.dat", buffer_nacf2, WINDOW_SIZE);
    p.write1DPlotData("plots/acf2_win.dat", buffer_acf2_win, WINDOW_SIZE);
    p.write1DPlotData("plots/snac.dat", buffer_snac, WINDOW_SIZE);
    p.write1DPlotData("plots/wsnac.dat", buffer_wsnac, WINDOW_SIZE);


    
    exit(0);
}
