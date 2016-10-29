#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "peakpicking.h"

#define THRESHOLD 0.8


peakpicking::peakpicking(double *input_data, int size){
    peakpicking::data_size = size;
    peakpicking::data = input_data;
}

double peakpicking::getPeriod(){
    //return getAllKeyMaximas().front();
    return getFirstKeyMaxima();
}


//QINT - quadratic interpolation of three adjacent samples
double peakpicking::qint_x(int i){
    double alpha = data[i-1];
    double beta = data[i];
    double gamma = data[i+1];
    return 0.5 * (alpha - gamma) / (alpha - 2*beta + gamma);
}

//QINT - quadratic interpolation of three adjacent samples
double peakpicking::qint_y(int i){
    double alpha = data[i-1];
    double beta = data[i];
    double gamma = data[i+1];
    double p = qint_x(i);
    return beta - 0.25 * (alpha - gamma) * p;
}

void peakpicking::showAllpeaks_x(){
    for(int i=0;i<data_size;i++){
        if (i > 0) {
            if (data[i-1] < data[i] && data[i+1] < data[i]){ 
                std::cout   <<  "x =" << i 
                            << "  y=" << data[i] 
                            << "  p=" << i + qint_x(i) 
                            << "  y(p)=" << qint_y(i) 
                            << std::endl;
            }
        }
    }
}


// Returns maximum peak
double peakpicking::get_n_max(){
    double max=-1;
    for(int i=0;i<data_size;i++){
        if (i > 0 && data[i] > max) {
            max = data[i];
        }
    }
    return max;
}

// Returns all of the maximas occuring after a
// zero crossed positive slope ending with a 
// with a negatively sloped zero crossing.
std::vector<double> peakpicking::getAllKeyMaximas(){
    std::vector<double> maximas;
    bool zerocrossed = false;
    double n_max = get_n_max();
    double max=-1;
    int max_x = 0;
    
    for(int i=0;i<data_size;i++){
        if (i > 0) {
            if(data[i-1] < 0 && data[i] >= 0){
                zerocrossed = true;
            }
            if(data[i-1] > 0 && data[i] <= 0 && zerocrossed){
                if (inside_threshold(max,n_max)){
                    maximas.push_back(max_x + qint_x(max_x)); // add 'real' key maxima
                }
                zerocrossed = false;
                max = 0;
            }
            if(zerocrossed && i == data_size-1){
                if (inside_threshold(max,n_max)){
                    maximas.push_back(qint_x(max_x)); // add last ket maxima without negative zero
                }
                max = 0;
            }
            if (zerocrossed && data[i-1] < data[i] && data[i+1] < data[i]){
                if (data[i] > max){
                    max = data[i];
                    max_x = i;
                }
            }
        }
    }
    return maximas;
}


// Returns first of the maximas occuring after a
// zero crossed positive slope ending with a 
// with a negatively sloped zero crossing.
double peakpicking::getFirstKeyMaxima(){
    bool zerocrossed = false;
    double n_max = get_n_max();
    double max=-1;
    int max_x = 0;
    
    for(int i=0;i<data_size;i++){
        if (i > 0) {
            if(data[i-1] < 0 && data[i] >= 0){
                zerocrossed = true;
            }
            if(data[i-1] > 0 && data[i] <= 0 && zerocrossed){
                if (inside_threshold(max,n_max)){
                    return max_x + qint_x(max_x); // add 'real' key maxima
                }
                zerocrossed = false;
                max = 0;
            }
            if(zerocrossed && i == data_size-1){
                if (inside_threshold(max,n_max)){
                   return qint_x(max_x); // add last ket maxima without negative zero
                }
                max = 0;
            }
            if (zerocrossed && data[i-1] < data[i] && data[i+1] < data[i]){
                if (data[i] > max){
                    max = data[i];
                    max_x = i;
                }
            }
        }
    }
    return 0;
}



bool peakpicking::inside_threshold(double candidate, double n_max){
    return (candidate >= (n_max*THRESHOLD));
}

/* Measure maximum peak amplitude. */
double peakpicking::getMaxAmplitude(){
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









