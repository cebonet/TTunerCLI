#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "portaudio.h"
#include "../src/autocorrelation.h"
#include "../src/wavReader.h"
#include "../src/peakpicking.h"
#include "../src/peakpicking.h"



#define SAMPLE_RATE 44100
#define WINDOW_SIZE 1024
#define WIN_HAMMING 1
#define WIN_HANN 2
#define WIN_SINE 3

double truncate(double v, int p){
    double f = pow(10,p);
    return round(v*f)/f;
}

SCENARIO("Pitch from pure sinus signal 329.628:", "[pitch autocorrelation 329.628]")
{
    GIVEN("Buffers and sinus signal")
    {
        double period, frequency;

        // Buffers
        double* buffer_pcm = (double*) malloc(sizeof(double)*WINDOW_SIZE);
        double* buffer_window = (double*) malloc(sizeof(double)*WINDOW_SIZE);
        double* buffer_acf = (double*) malloc(sizeof(double)*WINDOW_SIZE);
        double* buffer_acf2 = (double*) malloc(sizeof(double)*WINDOW_SIZE);
        double* buffer_nacf2 = (double*) malloc(sizeof(double)*WINDOW_SIZE);
        double* buffer_acf2_win = (double*) malloc(sizeof(double)*WINDOW_SIZE);
        double* buffer_snac = (double*) malloc(sizeof(double)*WINDOW_SIZE);
        double* buffer_wsnac = (double*) malloc(sizeof(double)*WINDOW_SIZE);
      
        // Instantiate
        wavReader r = wavReader("soundSamples/329.628.wav", WINDOW_SIZE);
        peakpicking pick = peakpicking(WINDOW_SIZE);
        autocorrelation acf = autocorrelation(WINDOW_SIZE);

        // getAudio 
        int sr = r.getWavBuffer(buffer_pcm); 
       
        // Apply functions
        acf.window(WIN_HANN, buffer_window);
        acf.autocorrelation_acf(buffer_pcm, buffer_acf);
        acf.autocorrelation_acf2(buffer_pcm, buffer_acf2);
        acf.autocorrelation_acf2(buffer_pcm, buffer_acf2_win, buffer_window);
        acf.autocorrelation_nacf2(buffer_pcm, buffer_nacf2);
        acf.autocorrelation_snac(buffer_pcm, buffer_snac);
        acf.autocorrelation_snac(buffer_pcm, buffer_wsnac, buffer_window);

        WHEN("We use ACF")
        {
            period = pick.getPeriod(buffer_acf);
                REQUIRE(truncate(sr/period,3) == 329.628 );
        }

        WHEN("We use ACF type 2")
        {
            period = pick.getPeriod(buffer_acf2);
                REQUIRE(truncate(sr/period,3) == 329.628 );
        }

        WHEN("We use normalized - ACF type 2")
        {
            period = pick.getPeriod(buffer_nacf2);
                REQUIRE(truncate(sr/period,3) == 329.628 );
        }
        
        WHEN("We use windowed ACF type 2")
        {
            period = pick.getPeriod(buffer_acf2_win);
                
            REQUIRE(truncate(sr/period,3) == 329.628 );
        }
        
        WHEN("We use SNAC")
        {
            period = pick.getPeriod(buffer_snac);
                REQUIRE(truncate(sr/period,3) == 329.628 );
        }
        
        WHEN("We use windowed SNAC")
        {
            period = pick.getPeriod(buffer_wsnac);
                REQUIRE(truncate(sr/period,3) == 329.628 );
        }
    }
}





