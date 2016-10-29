#ifndef PEAK_PICKING_H
#define PEAK_PICKING_H
#include<vector>


class peakpicking {
private:
    int data_size;
    double * data;
    double get_n_max();
    bool inside_threshold(double candidate, double n_max);
    std::vector<double> getAllKeyMaximas();
    peakpicking () {}

public:
    peakpicking(double* input_data, int size);
    double getMaxAmplitude();
    double getFirstKeyMaxima();
    double getPeriod();
    double qint_x(int i);
    double qint_y(int i);
    void showAllpeaks_x();
};

#endif
