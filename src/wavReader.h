#ifndef WAV_READER_H
#define WAV_READER_H

class wavReader {
private:
    const char* fname;
    int buffer_size;
    wavReader () {}

public:
    wavReader(const char *filename, int size);
    void  getWavBuffer(short* buffer);
};

#endif