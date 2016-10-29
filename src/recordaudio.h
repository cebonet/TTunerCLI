#ifndef RECORD_AUDIO_H
#define RECORD_AUDIO_H
#include "portaudio.h"

class recordaudio {

private:
    PaStreamParameters inputParameters;
    PaError err;
    PaStream *stream;
    void error();

public:
    recordaudio();
    bool getAudioStream(double *buffer);
    void closeStream();
};

#endif
