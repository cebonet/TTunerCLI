#!/usr/bin/python

# Need to import the plotting package:
import matplotlib.pyplot as plt
import numpy as np
import math


def plot1D(filename):
    fig = plt.figure()
    data = np.loadtxt(filename)
    ax = fig.add_subplot(1,1,1)
    ax.plot(data)
    plt.show()
    return;
