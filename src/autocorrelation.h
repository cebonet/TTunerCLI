#ifndef AUTO_CORRELATION_H
#define AUTO_CORRELATION_H

class autocorrelation {

private:
    short* buffer;
    int window_size;
    float n_prime(int lag, short* data);
    float n_prime_win(int lag, int window_type, short* data);
    float m_prime(int lag, short* data);
    float m_prime_win(int lag, int window_type, short* data);
    float r(int lag, short* data);
    float r_prime(int lag, short* data);
    float r_prime_win(int lag, int window_type, short* data);
    float w_hamming(int n);
    float w_hann(int n);
    autocorrelation(){};

public:
    autocorrelation(int size);
    void autocorrelation_acf(short* data, float* output);
    void autocorrelation_acf2(short* data, float* output);
    void autocorrelation_nacf2(short* data, float* output);
    void autocorrelation_acf2_win(short* data, float* output);
    void autocorrelation_snac(short* data, float* output);
    void autocorrelation_wsnac(short* data, int window_type, float* output);
    void window(int type, float* output);
};

#endif
