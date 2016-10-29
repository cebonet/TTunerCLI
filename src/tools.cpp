#include "tools.h"

tools::tools(double *input_data, int size){
    tools::data_size = size;
    tools::data = input_data;
}

    
    
/* Measure maximum peak amplitude. */
double tools::getMaxAmplitude(){
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