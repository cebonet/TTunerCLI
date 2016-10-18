#include "autocorrelation.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265


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

void autocorrelation::autocorrelation_acf(double* data, double* output){
    for (int lag=0; lag <= window_size/2; lag++){
       output[lag]  = r(lag,data);
    }
}

/*
 * Autocorrelation Function (ACF)
 * Type II
 */

void autocorrelation::autocorrelation_acf2(double* data, double* output){
    for (int lag=0; lag < window_size; lag++){
       output[lag]  = r_prime(lag,data);
    }
}

/*
 * Windowed Autocorrelation Function (WAC)
 * Type II
 */

void autocorrelation::autocorrelation_acf2(double* data, double* output, double* window){
    for (int lag=0; lag < window_size; lag++){
        output[lag]  = r_prime(lag, data, window);
    }
}

/*
 * Normalised Autocorrelation Function (NAC)
 * Type II
 */

void autocorrelation::autocorrelation_nacf2(double* data, double* output){
    double maximum = 0;
    for (int lag=0; lag < window_size; lag++){
        if(lag == 0){
            maximum = r_prime(lag,data);
        }
        output[lag]  = r_prime(lag,data)/maximum;
    }
}


/*
 * Specially Normalised Autocorrelation Function (SNAC)
 */

void autocorrelation::autocorrelation_snac(double* data, double* output){
    for (int lag=0; lag < window_size; lag++){
        output[lag] = n_prime(lag,data);
    }
}



/*
 * Windowed Special Normalised Autocorrelation Function (WSNAC)
 */

void autocorrelation::autocorrelation_snac(double* data, double* output, double* window){
    for (int lag=0; lag < window_size; lag++){
        output[lag] = n_prime(lag, data, window);
    }
}


/*
 *
 * Auxiliary functions
 *
 */

double autocorrelation::r(int lag, double* data){
    double sum = 0;
    
    for (int j=0; j <= window_size/2-1; j++){
        sum += data[j]*data[j+lag];
    }
    return sum;
}

double autocorrelation::r_prime(int lag, double* data){
    double sum = 0;
    for (int j=0; j <= window_size - 1 - lag; j++){
       sum += data[j] * data[j+lag];
    }
    return sum;
}


double autocorrelation::r_prime(int lag, double* data, double* window){
    double sum = 0;
    for (int j=0; j <= window_size - 1 - lag; j++){
       sum += window[j] * data[j] * window[j+lag] * data[j+lag];
    }
    return sum;
}

double autocorrelation::m_prime(int lag, double* data){
    double sum = 0;
    for (int j=0; j <= window_size - 1 - lag; j++){
        sum += (data[j]*data[j] + data[j+lag] * data[j+lag]);
    }
    return sum;
} 

double autocorrelation::m_prime(int lag, double* data, double* window){
    double sum1 = 0;    
    double sum2 = 0;
    
    for (int j=0; j <= window_size - 1 - lag; j++){
        sum1 += data[j] * data[j] * window[j] * window[j+lag];    
    }
    
    for (int j=0; j <= window_size - 1 - lag; j++){
        sum2 += data[j+lag] * data[j+lag] * window[j+lag] * window[j];    
    }
    return sum1 + sum2;
} 


double autocorrelation::n_prime(int lag, double* data){
    return ( 2 * r_prime(lag, data)) / m_prime(lag, data);
}

double autocorrelation::n_prime(int lag, double* data, double* window){
    return (2 * r_prime(lag, data, window)) / m_prime(lag, data, window);
}


void autocorrelation::window(int type,double* output){
    for (int j=0; j < window_size; j++){
        if (type == 1) {
            output[j] = w_hamming(j);
        }
        if (type == 2) {
            output[j] = w_hann(j);
        }
        if (type == 3) {
            output[j] = w_sine(j);
        }
    }
}

// Hamming window (1)
double autocorrelation::w_hamming(int n){
    return 0.53836 - (0.46164 * cos((2 * PI * n)/ window_size));
}

// Hann window (2)
double autocorrelation::w_hann(int n){
    return  0.5 * (1- cos( (2 * PI * n) / window_size));
}

// Sine window (3)
double autocorrelation::w_sine(int n){
    return sin(PI*n/window_size);
}
