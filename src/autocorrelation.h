#ifndef AUTO_CORRELATION_H
#define AUTO_CORRELATION_H

class autocorrelation {

private:
    short* buffer;
    int window_size;
    double n_prime(int lag, short* data);
    double n_prime_win(int lag, int window_type, short* data);
    double m_prime(int lag, short* data);
    double m_prime_win(int lag, int window_type, short* data);
    double r(int lag, short* data);
    double r_prime(int lag, short* data);
    double r_prime_win(int lag, int window_type, short* data);
    double w_hamming(int n);
    double w_hann(int n);
    double w_sine(int n);
    autocorrelation(){};

public:
    autocorrelation(int size);
    void autocorrelation_acf(short* data, double* output);
    void autocorrelation_acf2(short* data, double* output);
    void autocorrelation_nacf2(short* data, double* output);
    void autocorrelation_acf2_win(short* data, double* output);
    void autocorrelation_snac(short* data, double* output);
    void autocorrelation_wsnac(short* data, int window_type, double* output);
    void window(int type, double* output);
};

#endif
