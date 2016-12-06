#include "tools.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <sstream>
#define BASE_A4 440

using namespace std;

string const tools::notes[] = {"C ","C#","D ","D#","E ","F ","F#","G ","G#","A ","A#","B "};
string const tools::cagri = "Cagri is here!";

tools::tools(int size){
    tools::data_size = size;
}
    
/* Measure maximum peak amplitude. */
double tools::getMaxAmplitude(double *data){
    double max, average, val;
    max = 0;
    average = 0;
    for(int i=0; i< data_size; i++ ){
        val = data[i];
        if( val < 0 ) val = -val; /* ABS */
        if( val > max ){
            max = val;
        }
        average += val;
    }
    average = average / data_size;
    return average;
}


int tools::getMIDI(double f){
    //return round(12 * log2(f / BASE_A4))+57;
    return round(69 + 12 * log2(f/BASE_A4));
}

std::string tools::getMIDIasNote(double f){
    int n = getMIDI(f);
    if (n >= 0 && n <= 119){
        return notes[n % 12] + numberToString((n/12) );
    }
    return "N/A";
}
 
double tools::noteToFrequency(int n){
    double result= 0;
    if (n >= 0 && n <= 119){
        result = BASE_A4 * pow(2,(n-69.0)/12.0);
    }
    return result;
}
int tools::midiNoteStringToNumber(string s){
    int c,i;
    int result = -1;
    if (s.length() == 3){
        for (int i = 0; i < 12;i++){
            if (notes[i].at(0) == s.at(0)){
                c = i;
                char c = s.at(2);
                int ic = c - '0';
                i = ic;
                result = i*12+c;
            }
        }
    }
    return result;
}

// AUX
string tools::numberToString (int number){
    ostringstream ss;
    ss.clear();
    ss << number;
    return ss.str();
}


/*
void tools::butterworth_filter(double *data, int window_size, int sr, int cutOff){
    double* audioData[1];
    audioData[0] = new double[window_size];
    Dsp::Filter* f = new Dsp::FilterDesign
      <Dsp::Butterworth::Design::HighPass <2> >;
    Dsp::Params params;
    params[0] = sr; // sample rate
    params[1] = 2; // order
    params[2] = cutOff; // corner frequency
    f->setParams (params);
    f->process (window_size, audioData);
}
*/
