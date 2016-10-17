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

void autocorrelation::autocorrelation_acf(short* data, double* output){
    for (int lag=0; lag <= window_size/2; lag++){
       output[lag]  = r(lag,data);
    }
}

/*
 * Autocorrelation Function (ACF)
 * Type II
 */

void autocorrelation::autocorrelation_acf2(short* data, double* output){
    for (int lag=0; lag < window_size; lag++){
       output[lag]  = r_prime(lag,data);
    }
}

/*
 * Normalised Autocorrelation Function (NAC)
 * Type II
 */

void autocorrelation::autocorrelation_nacf2(short* data, double* output){
    double maximum = 0;
    for (int lag=0; lag < window_size; lag++){
        if(lag == 0){
            maximum = r_prime(lag,data);
        }
        output[lag]  = r_prime(lag,data)/maximum;
    }
}

/*
 * Windowed Autocorrelation Function (WAC)
 * Type II
 */

void autocorrelation::autocorrelation_acf2_win(short* data, double* output){
    for (int lag=0; lag < window_size; lag++){
        output[lag]  = r_prime_win(lag, 1, data);
    }
}

/*
 * Specially Normalised Autocorrelation Function (SNAC)
 */

void autocorrelation::autocorrelation_snac(short* data, double* output){
    for (int lag=0; lag < window_size; lag++){
        output[lag] = n_prime(lag,data);
    }
}

/*
 * Windowed Special Normalised Autocorrelation Function (WSNAC)
 */

void autocorrelation::autocorrelation_wsnac(short* data, int window_type, double* output){
    for (int lag=0; lag < window_size; lag++){
        output[lag] = n_prime_win(lag, window_type, data);
    }
}


/*
 *
 * Auxiliary functions
 *
 */

double autocorrelation::r(int lag, short* data){
    double sum = 0;
    
    for (int j=0; j <= window_size/2-1; j++){
        sum += data[j]*data[j+lag];
    }
    return sum;
}

double autocorrelation::r_prime(int lag, short* data){
    double sum = 0;
    
    for (int j=0; j <= window_size - 1 - lag; j++){
       sum += data[j] * data[j+lag];
    }
    return sum;
}

double autocorrelation::r_prime_win(int lag, int window_type, short* data){
    double sum = 0;
    double* w = (double*) malloc(sizeof(double)*window_size);
    
    window(window_type,w);
    for (int j=0; j <= window_size - 1 - lag; j++){
       sum += w[j] * data[j] * w[j+lag] * data[j+lag];
    }
    return sum;
}

double autocorrelation::m_prime(int lag, short* data){
    double sum = 0;
    for (int j=0; j <= window_size - 1 - lag; j++){
        sum += (data[j]*data[j] + data[j+lag] * data[j+lag]);
    }
    return sum;
} 

double autocorrelation::m_prime_win(int lag, int window_type, short* data){
    double sum1 = 0;    
    double sum2 = 0;
    double* w= (double*) malloc(sizeof(double)*window_size);
    window(window_type,w);
    
    for (int j=0; j <= window_size - 1 - lag; j++){
        sum1 += data[j] * data[j] * w[j] * w[j+lag];    
    }
    
    for (int j=0; j <= window_size - 1 - lag; j++){
        sum2 += data[j+lag] * data[j+lag] * w[j+lag] * w[j];    
    }
    return sum1 + sum2;
}

double autocorrelation::n_prime(int lag, short* data){
    return ( 2 * r_prime(lag, data)) / m_prime(lag, data);
}

double autocorrelation::n_prime_win(int lag, int window_type, short* data){
    return ( 2 * r_prime_win(lag,window_type, data)) / m_prime_win(lag, window_type, data);
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
