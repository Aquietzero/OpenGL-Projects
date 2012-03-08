#ifndef VECTOR_H
#define VECTOR_H

#include "stdincludes.h"

/* Class Vector2D will not provide implicit ceocion. So make sure that
 * you don't add, subtraction different kinds of vectors, even though
 * they are of built-in types.
 */
template<class V_TYPE>
class Vector2D {

    public:
        Vector2D();
        Vector2D(V_TYPE m, V_TYPE n);
        Vector2D(const Vector2D& v);
        ~Vector2D() {};

        Vector2D operator+(const Vector2D& v) const; // addition
        Vector2D operator-(const Vector2D& v) const; // subtraction
        Vector2D operator*(const V_TYPE s) const; // scale

        V_TYPE operator*(const Vector2D& v) const; // dot product
        V_TYPE cross(const Vector2D& v) const; // cross product

        double normal() const; // the precision of this method is raised to the highest 'double'
        Vector2D<V_TYPE> normalize(); // the precision of this method depends on the V_TYPE

        Vector2D& operator=(const Vector2D& v);
        
        V_TYPE x;
        V_TYPE y;

};

// Constructors.
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

// Basic Operations: Addition, Subtraction, Scale.
template<class V_TYPE>
Vector2D<V_TYPE> Vector2D<V_TYPE>::operator+(const Vector2D<V_TYPE>& v) const {
    return Vector2D<V_TYPE>(x+v.x, y+v.y);
}

template<class V_TYPE>
Vector2D<V_TYPE> Vector2D<V_TYPE>::operator-(const Vector2D<V_TYPE>& v) const {
    return Vector2D<V_TYPE>(x-v.x, y-v.y);
}

template<class V_TYPE>
Vector2D<V_TYPE> Vector2D<V_TYPE>::operator*(const V_TYPE s) const {
    return Vector2D<V_TYPE>(x*s, y*s);
}

// Dot product and Cross product.
template<class V_TYPE>
V_TYPE Vector2D<V_TYPE>::operator*(const Vector2D<V_TYPE>& v) const {
    return (V_TYPE)(x*v.x + y*v.y);
}

template<class V_TYPE>
V_TYPE Vector2D<V_TYPE>::cross(const Vector2D& v) const {
    return (V_TYPE)(x*v.y - y*v.x);
}

// Copy constructor.
template<class V_TYPE>
Vector2D<V_TYPE>& Vector2D<V_TYPE>::operator=(const Vector2D<V_TYPE>& v) {
    if (&v != this)
        this->x = v.x, this->y = v.y;
    return *this;
}

// Normalizations.
template<class V_TYPE>
double Vector2D<V_TYPE>::normal() const {
    return sqrt((double)x*x + (double)y*y);
}

template<class V_TYPE>
Vector2D<V_TYPE> Vector2D<V_TYPE>::normalize() {
    V_TYPE n = normal();
    return Vector2D<V_TYPE>(x/n, y/n);
}



GLfloat* getNormalVector(
        GLfloat x1, GLfloat y1, GLfloat z1, 
        GLfloat x2, GLfloat y2, GLfloat z2);

#endif
