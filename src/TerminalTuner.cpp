#include "wavReader.h"
#include "autocorrelation.h"
#include "plotter.h"
#include "peakpicking.h"
#include "portaudio.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <alsa/asoundlib.h>
#include <unistd.h>
#include <algorithm>

#define SAMPLE_RATE	44100
#define WINDOW_SIZE 1024
#define WIN_HAMMING 1
#define WIN_HANN 2
#define WIN_SINE 3

#define NUM_CHANNELS    (1)
/* #define DITHER_FLAG     (paDitherOff)  */
#define DITHER_FLAG     (0) /**/
/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef double SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

using namespace std;

int main(){
    PaStreamParameters inputParameters;
    PaStream *stream;
    PaError err;
    int i;
    double max, average, val;
    double last_frequency=0;
    double period; 
    
    // Data buffers
    double* buffer = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    double* buffer_window = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    double* buffer_snac = (double*) malloc(sizeof(double)*WINDOW_SIZE);
    
    // Instantiate  
    autocorrelation acf = autocorrelation(WINDOW_SIZE);
    acf.window(WIN_SINE, buffer_window);
    peakpicking pick = peakpicking(buffer_snac, WINDOW_SIZE);
    plotter p = plotter();    
    

    if (buffer == NULL){
        printf("Could not allocate record array.\n");
        exit(1);
    }

    err = Pa_Initialize();
    if( err != paNoError ) goto error;
    
    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (inputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default input device.\n");
      goto error;
    }

    inputParameters.channelCount = NUM_CHANNELS;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    /* Record some audio. -------------------------------------------- */
    err = Pa_OpenStream(
              &stream,
              &inputParameters,
              NULL,                  /* &outputParameters, */
              SAMPLE_RATE,
              WINDOW_SIZE,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              NULL, /* no callback, use blocking API */
              NULL ); /* no callback, so no callback userData */
    
    
    if( err != paNoError ) goto error;
    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;
    cout << "Now recording!!" << endl;

    while (true){
        err = Pa_ReadStream(stream, buffer, WINDOW_SIZE);
        if( err != paNoError ) goto error;
        
        /* Measure maximum peak amplitude. */
        max = 0;
        average = 0;
        for( i=0; i< WINDOW_SIZE; i++ ){
            val = buffer[i];
            if( val < 0 ) val = -val; /* ABS */
            if( val > max )
            {
                max = val;
            }
            average += val;
        }

        average = average / WINDOW_SIZE;
       
        // Autocorrelation functions
        acf.autocorrelation_snac(buffer, buffer_snac);

        // Peak Picking
        period = pick.getPeriod();
        //cout << "Period: " << period << endl;
        if (average > 3e-015){
            last_frequency = SAMPLE_RATE/period;
            cout  << "\r" << "frequency: " << last_frequency << "  "  << flush;
            if (last_frequency > 600 && last_frequency < 700 ){
                p.write1DPlotData("plots/recorded.dat", buffer, WINDOW_SIZE);
                p.write1DPlotData("plots/recorded_snac.dat", buffer_snac, WINDOW_SIZE);
                cout << "plot written !" << endl;
             }
        }else{
            cout  << "\r" << "frequency: " << last_frequency << "  "  << flush;
        }
    }

    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;

error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return -1;
}
