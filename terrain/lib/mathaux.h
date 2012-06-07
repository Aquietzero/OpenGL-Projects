#ifndef MATH_AUX_H
#define MATH_AUX_H

#include "stdincludes.h"

#define PI 3.1415926

double radians(double degrees);
double degrees(double radians);

int closestPowerOf2lt(int num);
int closestPowerOf2gt(int num);

bool isPowerOf2(int num);

#endif
