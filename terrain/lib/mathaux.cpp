#include "mathaux.h"

double radians(double degrees) {
    return degrees*PI/180.0;
}

double degrees(double radians) {
    return radians*180.0/PI;
}

int closestPowerOf2lt(int num) {
    int ctr = 0;
    while (num >> ctr) ctr++;
    return pow(2, ctr-1);
}

int closestPowerOf2gt(int num) {
    int ctr = 0;
    while (num >> ctr) ctr++;
    return pow(2, ctr);
}

bool isPowerOf2(int num) {
    return closestPowerOf2lt(num) == num ? true : false;
}
