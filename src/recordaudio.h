#ifndef RECORD_AUDIO_H
#define RECORD_AUDIO_H
#include "portaudio.h"

class recordaudio {

private:
    PaStreamParameters inputParameters;
    PaError err;
    PaStream *stream;
    int samplerate;
    int device;
    void error();

public:
    recordaudio(bool verbose);
    bool openStream();
    bool getAudioStream(double *buffer);
    void closeStream();
};

#endif
