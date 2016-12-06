#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "peakpicking.h"
#define THRESHOLD 0.8


peakpicking::peakpicking(int size){
    peakpicking::data_size = size;
}

double peakpicking::getPeriod(double* data){
    //return getAllKeyMaximas().front();
    return getFirstKeyMaxima(data);
}


//QINT - quadratic interpolation of three adjacent samples
double peakpicking::qint_x(double* data, int i){
    double alpha = data[i-1];
    double beta = data[i];
    double gamma = data[i+1];
    return 0.5 * (alpha - gamma) / (alpha - 2*beta + gamma);
}

//QINT - quadratic interpolation of three adjacent samples
double peakpicking::qint_y(double* data, int i){
    double alpha = data[i-1];
    double beta = data[i];
    double gamma = data[i+1];
    double p = qint_x(data,i);
    return beta - 0.25 * (alpha - gamma) * p;
}

void peakpicking::showAllpeaks_x(double* data){
    for(int i=0;i<data_size;i++){
        if (i > 0) {
            if (data[i-1] < data[i] && data[i+1] < data[i]){ 
                std::cout   <<  "x =" << i 
                            << "  y=" << data[i] 
                            << "  p=" << i + qint_x(data,i) 
                            << "  y(p)=" << qint_y(data,i) 
                            << std::endl;
            }
        }
    }
}


// Returns maximum peak
double peakpicking::get_n_max(double* data){
    double max=-1;
    for(int i=0;i<data_size;i++){
        if (i > 0 && data[i] > max && data[i-1] < data[i]) {
            max = data[i];
        }
    }
    return max;
}

// Returns all of the maximas occuring after a
// zero crossed positive slope ending with a 
// with a negatively sloped zero crossing.
std::vector<double> peakpicking::getAllKeyMaximas(double *data){
    std::vector<double> maximas;
    bool zerocrossed = false;
    double n_max = get_n_max(data);
    double max=-1;
    int max_x = 0;
    
    for(int i=0;i<data_size;i++){
        if (i > 0) {
            if(data[i-1] < 0 && data[i] >= 0){
                zerocrossed = true;
            }
            if(data[i-1] > 0 && data[i] <= 0 && zerocrossed){
                if (inside_threshold(max,n_max)){
                    maximas.push_back(max_x + qint_x(data, max_x)); // add 'real' key maxima
                }
                zerocrossed = false;
                max = 0;
            }
            if(zerocrossed && i == data_size-1){
                if (inside_threshold(max,n_max)){
                    maximas.push_back(qint_x(data, max_x)); // add last ket maxima without negative zero
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
double peakpicking::getFirstKeyMaxima(double* data){
    bool zerocrossed = false;
    double n_max = get_n_max(data);
    double max=-1;
    int max_x = 0;
    
    for(int i=0;i<data_size;i++){
        if (i > 0) {
            if(data[i-1] < 0 && data[i] >= 0){
                zerocrossed = true;
            }
            if(data[i-1] > 0 && data[i] <= 0 && zerocrossed){
                if (inside_threshold(max,n_max)){
                    return max_x + qint_x(data, max_x); // add 'real' key maxima
                }
                zerocrossed = false;
                max = 0;
            }
            if(zerocrossed && i == data_size-1){
                if (inside_threshold(max,n_max)){
                   return qint_x(data, max_x); // add last key maxima without negative zero
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










