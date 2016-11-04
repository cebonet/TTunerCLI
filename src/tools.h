#ifndef TOOLS_H
#define TOOLS_H

class tools{
private:
    int data_size;
    double * data;
    tools () {}

public:
    tools(int size);
    double getMaxAmplitude(double *data);
    void butterworth_filter(float cutoff_frequency, float sampling_rate, double *data);

};
#endif
