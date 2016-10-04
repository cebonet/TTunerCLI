#include "autocorrelation.h"
#include <iostream>
#include <stdio.h>



/*
 * This class contains various autocorrelation functions.
 *
 */

autocorrelation::autocorrelation(int size){
    autocorrelation::window_size = size;
}

/*
 * Squared Normalised Autocorrelation Function (SNAC)
 *
 */

void autocorrelation::autocorrelation_snac(short* data, float* output){
    float n_prime = 0;
    for (int lag=0; lag <= window_size; lag++){
        n_prime = (float) (2 * r_prime(lag, data, window_size))/m_prime(lag,data,window_size);
        output[lag] = n_prime;
    }
}


int r_prime(int lag, short* data, int window_size){
    int sum = 0;
    for (int j=0; j <= window_size - 1 - lag; j++){
       sum += data[j] * data[j+lag];
    }
    return sum;
}

int m_prime(int lag, short* data, int window_size){
    int sum = 0;
    for (int j=0; j <= window_size - 1 - lag; j++){
        sum += (data[j]*data[j] + data[j+lag] * data[j+lag]);
    }
    return sum;
} 


/*
 * Windowed Squared Normalised Autocorrelation Function (WSNAC)
 *
 */


