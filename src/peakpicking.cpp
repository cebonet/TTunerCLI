#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "peakpicking.h"


peakpicking::peakpicking(float *input_data, int size){
    peakpicking::data_size = size;
    peakpicking::data = input_data;
}

float peakpicking::qint_x(float alpha, float beta, float gamma){
    return 0.5 * ( (alpha - gamma)  / (alpha - (2*beta) + gamma));
}


float peakpicking::qint_y(float alpha, float beta, float gamma){
    float p = qint_x(alpha,beta,gamma);
    return beta - 0.25 * ( alpha - gamma ) * p;
}

void peakpicking::getpeaks_x(){
    for(int i=0;i<data_size;i++){
        if (data[i-1] < data[i] && data[i+1] < data[i]){
            std::cout <<  "x =" << i << "  y=" << data[i] << "  p=" << i + qint_x(data[i-1],data[i],data[+1]) << "  y(p)=" << qint_y(data[i-1],data[i],data[+1]) << std::endl;
        }
    }
}



//%QINT - quadratic interpolation of three adjacent samples
//% [p,y,a] = qint(ym1,y0,yp1)
//%
//% returns the extremum location p, height y, and half-curvature a
//% of a parabolic fit through three points.
//% Parabola is given by y(x) = a*(x-p)^2+b,
//% where y(-1)=ym1, y(0)=y0, y(1)=yp1.
//p = (yp1 - ym1)/(2*(2*y0 - yp1 - ym1));
//y = y0 - 0.25*(ym1-yp1)*p;
//a = 0.5*(ym1 - 2*y0 + yp1);



