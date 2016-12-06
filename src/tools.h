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
    int midiNoteStringToNumber(std::string s);
    int getMIDI(double frequency);
    double noteToFrequency(int n);
    std::string getMIDIasNote(double f);
    //void butterworth_filter(double *data, int window_size, int sr, int cutOff);
};
#endif
