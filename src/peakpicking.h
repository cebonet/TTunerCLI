#ifndef PEAK_PICKING_H
#define PEAK_PICKING_H
#include<vector>


class peakpicking {
private:
    int data_size;
    double get_n_max(double* data);
    std::vector<double> getAllKeyMaximas(double* data);
    bool inside_threshold(double candidate, double n_max);
    double getFirstKeyMaxima(double* data);
    peakpicking () {}

public:
    peakpicking(int size);
    double getMaxAmplitude(double* data);
    double getPeriod(double* data);
    double qint_x(double* data, int i);
    double qint_y(double* data, int i);
    void showAllpeaks_x(double* data);
};

#endif
