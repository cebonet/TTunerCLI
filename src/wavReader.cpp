#include "wavReader.h"
#include <iostream>
#include <stdio.h>
#include <sndfile.hh>


wavReader::wavReader(const char *filename, int size){
    wavReader::fname = filename;
    wavReader::buffer_size = size;
}

void  wavReader::getWavBuffer(short* buffer){
	SndfileHandle file;
	file = SndfileHandle (fname) ;
	file.read (buffer, buffer_size) ;
}
