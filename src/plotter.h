#ifndef PLOTTER_H
#define PLOTTER_H


class plotter{


public:
plotter();
void write1DPlotData(const char* filename, short * data, int data_size);
void write1DPlotData(const char* filename, double * data, int data_size);

    
};
#endif
