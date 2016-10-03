#include "wavReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define WINDOW_SIZE 1024 

using namespace std;

int main(){
    short* buffer = (short*) malloc(sizeof(short)*WINDOW_SIZE);
    wavReader r = wavReader("329.628.wav", WINDOW_SIZE);
    r.getWavBuffer(buffer);
    
    cout << buffer[100] << endl;
    cout << buffer[200] << endl ;

    exit(0);
}
