#ifndef TOOLS_H
#define TOOLS_H
#include<string>

class tools{
private:
    int data_size;
    double * data;
    static std::string const notes[];
    static std::string const cagri;
    std::string numberToString (int number);
    tools () {}

public:
    tools(int size);
    double getMaxAmplitude(double *data);
    std::string getMIDI(double frequency);
    //void butterworth_filter(double *data, int window_size, int sr, int cutOff);
};
#endif
