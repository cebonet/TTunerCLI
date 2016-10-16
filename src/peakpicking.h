#ifndef PEAK_PICKING_H
#define PEAK_PICKING_H

class peakpicking {
private:
    int data_size;
    float * data;
    peakpicking () {}

public:
    peakpicking(float* input_data, int size);
    float qint_x(float alpha, float beta, float gamma);
    float qint_y(float alpha, float beta, float gamma);
    void getpeaks_x();
};

#endif
