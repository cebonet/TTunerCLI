#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <alsa/asoundlib.h>
#include <unistd.h>
#include <algorithm>
#include "recordaudio.h"

#define SAMPLE_RATE	44100
#define WINDOW_SIZE 1024
#define WIN_HAMMING 1
#define WIN_HANN 2
#define WIN_SINE 3

#define NUM_CHANNELS    (1)
/* #define DITHER_FLAG     (paDitherOff)  */
#define DITHER_FLAG     (0) /**/
/* Select sample format. */
#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"

using namespace std;

recordaudio::recordaudio( ){
    err = Pa_Initialize();
    
    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (inputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default input device.\n");
    }

    inputParameters.channelCount = NUM_CHANNELS;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;
    
    if( err != paNoError ) 
        error();
    
    err = Pa_OpenStream(
              &stream,
              &inputParameters,
              NULL,     /* &outputParameters, */
              SAMPLE_RATE,
              WINDOW_SIZE,
              paClipOff,/* we won't output out of range samples so don't bother clipping them */
              NULL,     /* no callback, use blocking API */
              NULL );   /* no callback, so no callback userData */
    
    err = Pa_StartStream( stream );
    cout << "Now recording!!" << endl;
    if( err != paNoError ) 
        error();

}

bool recordaudio::getAudioStream(double *buffer){
    err = Pa_StartStream( stream );
    err = Pa_ReadStream(stream, buffer, WINDOW_SIZE);
    if( err != paNoError ){
        error();
        return false;
    }
    return true;
}

void recordaudio::closeStream(){
    err = Pa_CloseStream( stream );
    if( err != paNoError ) 
        error();
}

void recordaudio::error(){
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
}


