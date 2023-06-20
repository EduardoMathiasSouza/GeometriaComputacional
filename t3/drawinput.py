#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
from matplotlib.lines import Line2D

[n, w] = list(map(int, input().split()))

for i in range(n):
    data = list(map(float, input().split()))
    x0 = data[0]
    x1 = data[1]
    y0 = data[2]
    y1 = data[3]
    
    plt.plot([x0, x1], [y0, y1], 'b-')
    
for i in range(w):
    data = list(map(float, input().split()))
    x0 = data[0]
    x1 = data[1]
    y0 = data[2]
    y1 = data[3]

    plt.plot([x0, x1], [y0, y0], 'r-')
    plt.plot([x0, x1], [y1, y1], 'r-')
    plt.plot([x0, x0], [y0, y1], 'r-')
    plt.plot([x1, x1], [y0, y1], 'r-')


plt.show()
