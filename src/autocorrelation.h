#ifndef AUTO_CORRELATION_H
#define AUTO_CORRELATION_H

class autocorrelation {

private:
    short* buffer;
    int window_size;
    int r_prime(int lag, short* data, int window_size);
    int m_prime(int lag, short* data, int window_size);
    autocorrelation(){};

public:
    autocorrelation(int size);
    void autocorrelation_snac(short* data, float* output);
    void autocorrelation_wsnac(short* data, float* output);
};

#endif
