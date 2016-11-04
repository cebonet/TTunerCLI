#include "tools.h"
#include "Iir.h"
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

void tools::butterworth_filter(float cutoff_frequency, float sampling_rate, double *data){
	const int order = 3;
    Iir::Butterworth::LowPass<order> f;
    f.setup (order, sampling_rate, cutoff_frequency);
    f.reset ();

    // let's generate an input signal and filter it instantly!
    for(int i=0;i<1000;i++) {
            float a=0;
            if (i==10) a = 1; // delta pulse at t=10
            float b = f.filter(a);
            //fprintf(fimpulse,"%f\n",b);
            std::cout << b << std::endl;
    }
}
