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
 * Autocorrelation Function (ACF)
 * Type I
 */

void autocorrelation::autocorrelation_acf(short* data, float* output){
    int max_index = 0;
    int max = 0;
    for (int lag=0; lag <= window_size/2; lag++){
       output[lag]  = r(lag,data);
       if (output[lag] > max){
            max_index = lag;
            max = output[lag];
       }
    }
    std::cout << max_index << std::endl;
}

/*
 * Autocorrelation Function (ACF)
 * Type II
 */

void autocorrelation::autocorrelation_acf2(short* data, float* output){
    for (int lag=0; lag < window_size; lag++){
       output[lag]  = r_prime(lag,data);
    }
}

/*
 * Normalised Autocorrelation Function (NAC)
 * Type II
 */

void autocorrelation::autocorrelation_nacf2(short* data, float* output){
    float maximum = 0;
    for (int lag=0; lag < window_size; lag++){
        if(lag == 0){
            maximum = r_prime(lag,data);
        }
        output[lag]  = r_prime(lag,data)/maximum;
    }
}

/*
 * Squared Normalised Autocorrelation Function (SNAC)
 */

void autocorrelation::autocorrelation_snac(short* data, float* output){
    float n_prime = 0;
    for (int lag=0; lag < window_size; lag++){
        n_prime = (float) (2 * r_prime(lag, data))/m_prime(lag,data);
        output[lag] = n_prime;
    }
}

/*
 * Windowed Squared Normalised Autocorrelation Function (WSNAC)
 */


/*
 *
 * Auxiliary functions
 *
 */


float autocorrelation::r(int lag, short* data){
    float sum = 0;
    for (int j=0; j <= window_size/2-1; j++){
        sum += data[j]*data[j+lag];
    }
    return sum;
}

float autocorrelation::r_prime(int lag, short* data){
    float sum = 0;
    for (int j=0; j <= window_size - 1 - lag; j++){
       sum += data[j] * data[j+lag];
    }
    return sum;
}


float autocorrelation::m_prime(int lag, short* data){
    float sum = 0;
    for (int j=0; j <= window_size - 1 - lag; j++){
        sum += (data[j]*data[j] + data[j+lag] * data[j+lag]);
    }
    return sum;
} 




