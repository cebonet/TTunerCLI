#ifndef AUTO_CORRELATION_H
#define AUTO_CORRELATION_H

class autocorrelation {

private:
    short* buffer;
    int window_size;
    int m_prime(int lag, short* data);
    int r_prime(int lag, short* data);
    int r(int lag, short* data);
    autocorrelation(){};

public:
    autocorrelation(int size);
    void autocorrelation_acf(short* data, float* output);
    void autocorrelation_acf2(short* data, float* output);
    void autocorrelation_nacf2(short* data, float* output);
    void autocorrelation_snac(short* data, float* output);
    void autocorrelation_wsnac(short* data, float* output);
};

#endif