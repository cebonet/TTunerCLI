#ifndef AUTO_CORRELATION_H
#define AUTO_CORRELATION_H

class autocorrelation {

private:
    double* buffer;
    int window_size;
    double n_prime(int lag, double* data);
    double n_prime(int lag, double* data, double* window);
    double m_prime(int lag, double* data);
    double m_prime(int lag, double* data, double* window);
    double r(int lag, double* data);
    double r_prime(int lag, double* data);
    double r_prime(int lag, double* data, double* window);
    double w_hamming(int n);
    double w_hann(int n);
    double w_sine(int n);
    autocorrelation(){};

public:
    autocorrelation(int size);
    void autocorrelation_acf(double* data, double* output);
    void autocorrelation_acf2(double* data, double* output);
    void autocorrelation_acf2(double* data, double* output, double* window);
    void autocorrelation_nacf2(double* data, double* output);
    void autocorrelation_snac(double* data, double* output);
    void autocorrelation_snac(double* data, double* output, double* window);
    void window(int type, double* output);
};

#endif
