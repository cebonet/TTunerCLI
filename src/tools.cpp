#include "tools.h"
#include "DSPFilters/Dsp.h"
#include <sstream>
#include <iostream>
#include <iomanip>

tools::tools(int size){
    tools::data_size = size;
}

    
    
/* Measure maximum peak amplitude. */
double tools::getMaxAmplitude(double *data){
    double max, average, val;
    max = 0;
    average = 0;
    for(int i=0; i< data_size; i++ ){
        val = data[i];
        if( val < 0 ) val = -val; /* ABS */
        if( val > max )
        {
            max = val;
        }
        average += val;
    }
    average = average / data_size;
    return average;
}

void tools::butterworth_filter(double *data, int window_size, int sr, int cutOff){
    double* audioData[1];
    audioData[0] = new double[window_size];
    Dsp::Filter* f = new Dsp::FilterDesign
      <Dsp::Butterworth::Design::HighPass <2> >;
    Dsp::Params params;
    params[0] = sr; // sample rate
    params[1] = 2; // order
    params[2] = cutOff; // corner frequency
    f->setParams (params);
    f->process (window_size, audioData);
}
