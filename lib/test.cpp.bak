#include <iostream>
#include "vector.h"

using namespace std;

int main() {

    Vector2D<double> v1(2, 9);
    Vector2D<double> v2(1, 2);
    Vector2D<double> v3, v4;

    v4 = v3 = v1 + v2;
    cout << v3.x << ", " << v3.y << endl;
    cout << v4.x << ", " << v4.y << endl;

    cout << "v4 * v3 = " << v4*v3 << endl;
    cout << "v4 cross v3 = " << v4.cross(v3) << endl;
    cout << "|v4| = " << v4.normal() << endl;

    v3 = v4.normalize();
    cout << "Normal(v4) = " << v3.x << ", " << v3.y << endl;

    return 0;

}
