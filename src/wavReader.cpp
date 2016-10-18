#include "wavReader.h"
#include <iostream>
#include <stdio.h>
#include <sndfile.hh>


wavReader::wavReader(const char *filename, int size){
    wavReader::fname = filename;
    wavReader::buffer_size = size;
    
}

int wavReader::getWavBuffer(double* buffer){
    SndfileHandle file;
	file = SndfileHandle (fname) ;
	printf ("Opened file '%s'\n", fname) ;
	printf ("    Sample rate : %d\n", file.samplerate ()) ;
	printf ("    Channels    : %d\n", file.channels ()) ;
	file.read (buffer, buffer_size) ;
    
    return file.samplerate();
}


