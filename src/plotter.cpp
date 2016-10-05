#include "plotter.h"
#include <iostream>
#include <fstream>

using namespace std;

plotter::plotter(){
}

void plotter::write1DPlotData(const char* filename, short * data, int data_size){
    fstream fs;
    fs.open (filename, fstream::out);

    for (int i=0; i < data_size; i++){
        fs << data[i] << endl;
    }
    fs.close();
}

void plotter::write1DPlotData(const char* filename, float * data, int data_size){
    fstream fs;
    fs.open (filename, fstream::out);

    for (int i=0; i < data_size; i++){
        fs << data[i] << endl;
    }
    fs.close();
}
