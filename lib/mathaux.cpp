#include "mathaux.h"

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
