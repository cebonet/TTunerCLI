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
