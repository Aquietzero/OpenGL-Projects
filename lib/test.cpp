#include <iostream>
#include "vector.h"

using namespace std;

int main() {

    Vector2D<int> v1(2, 9);
    Vector2D<int> v2(1, 2);
    Vector2D<int> v3;

    v3 = v1 + v2;
    cout << v3.x << ", " << v3.y << endl;

    return 0;

}
