#ifndef VECTOR_H
#define VECTOR_H

#include "stdincludes.h"

template<class V_TYPE>
class Vector2D {

    public:
        Vector2D();
        Vector2D(V_TYPE x, V_TYPE y);
        Vector2D(const Vector2D& v);
        ~Vector2D() {};

        Vector2D operator+(const Vector2D& v) const;

        Vector2D& operator=(const Vector2D& v);
        
        V_TYPE x;
        V_TYPE y;

};

template<class V_TYPE>
Vector2D<V_TYPE>::Vector2D() {
    x = 0;
    y = 0;
}

template<class V_TYPE>
Vector2D<V_TYPE>::Vector2D(V_TYPE m, V_TYPE n) {
    x = m;
    y = n;
}

template<class V_TYPE>
Vector2D<V_TYPE>::Vector2D(const Vector2D<V_TYPE>& v) { 
    x = v.x; 
    y = v.y; 
}

template<class V_TYPE>
Vector2D<V_TYPE> Vector2D<V_TYPE>::operator+(const Vector2D<V_TYPE>& v) const {

    return Vector2D<V_TYPE>(x+v.x, y+v.y);

}

template<class V_TYPE>
Vector2D<V_TYPE>& Vector2D<V_TYPE>::operator=(const Vector2D<V_TYPE>& v) {

    if (&v != this) {
        this->x = v.x;
        this->y = v.y;
    }
    return *this;

}

GLfloat* getNormalVector(
        GLfloat x1, GLfloat y1, GLfloat z1, 
        GLfloat x2, GLfloat y2, GLfloat z2);

#endif
