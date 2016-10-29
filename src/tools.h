#ifndef TOOLS_H
#define TOOLS_H

class tools{
private:
    int data_size;
    double * data;
    tools () {}

public:
    tools(double* input_data, int size);
    double getMaxAmplitude();
};

#endif
