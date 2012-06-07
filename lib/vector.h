#ifndef VECTOR_H
#define VECTOR_H

#include "stdincludes.h"

#define AVG4(x, y, m, n) ((x + y + m + n)/4.0)

/* Class Vector2D will not provide implicit ceocion. So make sure that
 * you don't add, subtraction different kinds of vectors, even though
 * they are of built-in types.
 */
template<class V_TYPE>
class Vector2D {

    public:
        Vector2D();
        Vector2D(V_TYPE, V_TYPE);
        Vector2D(const Vector2D&);
        ~Vector2D() {};

        Vector2D operator+(const Vector2D&) const; // addition
        Vector2D operator-(const Vector2D&) const; // subtraction
        Vector2D operator*(const V_TYPE) const; // scale

        V_TYPE operator*(const Vector2D&) const; // dot product
        V_TYPE cross(const Vector2D&) const; // cross product

        double normal() const; // the precision of this method is raised to the highest 'double'
        void normalize(); // the precision of this method depends on the V_TYPE

        Vector2D& operator=(const Vector2D&);
        
        V_TYPE x;
        V_TYPE y;

};

// Constructors.
template<class V_TYPE>
Vector2D<V_TYPE>::Vector2D() {
    x = y = 0;
}

template<class V_TYPE>
Vector2D<V_TYPE>::Vector2D(V_TYPE m, V_TYPE n) 
    : x(m), y(n) {
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
void Vector2D<V_TYPE>::normalize() {
    V_TYPE n = normal();
    x /= n;
    y /= n;
}


/* Class Vector3D will not provide implicit ceocion. So make sure that
 * you don't add, subtraction different kinds of vectors, even though
 * they are of built-in types.
 */
template<class V_TYPE>
class Vector3D {

    public:
        Vector3D();
        Vector3D(V_TYPE, V_TYPE, V_TYPE);
        Vector3D(const Vector3D&);
        ~Vector3D() {};

        Vector3D operator+(const Vector3D&) const; // addition
        Vector3D operator-(const Vector3D&) const; // subtraction
        Vector3D operator*(const V_TYPE) const; // scale

        V_TYPE operator*(const Vector3D&) const; // dot product
        Vector3D cross(const Vector3D&) const; // cross product

        double normal() const; // the precision of this method is raised to the highest 'double'
        void normalize(); // the precision of this method depends on the V_TYPE

        Vector3D& operator=(const Vector3D&);
        
        V_TYPE x;
        V_TYPE y;
        V_TYPE z;

};

// Constructors.
template<class V_TYPE>
Vector3D<V_TYPE>::Vector3D() {
    x = y = z = 0;
}

template<class V_TYPE>
Vector3D<V_TYPE>::Vector3D(V_TYPE v1, V_TYPE v2, V_TYPE v3)
    : x(v1), y(v2), z(v3) {
}

template<class V_TYPE>
Vector3D<V_TYPE>::Vector3D(const Vector3D<V_TYPE>& v) { 
    x = v.x; 
    y = v.y; 
    z = v.z; 
}

// Basic Operations: Addition, Subtraction, Scale.
template<class V_TYPE>
Vector3D<V_TYPE> Vector3D<V_TYPE>::operator+(const Vector3D<V_TYPE>& v) const {
    return Vector3D<V_TYPE>(x+v.x, y+v.y, z+v.z);
}

template<class V_TYPE>
Vector3D<V_TYPE> Vector3D<V_TYPE>::operator-(const Vector3D<V_TYPE>& v) const {
    return Vector3D<V_TYPE>(x-v.x, y-v.y, z-v.z);
}

template<class V_TYPE>
Vector3D<V_TYPE> Vector3D<V_TYPE>::operator*(const V_TYPE s) const {
    return Vector3D<V_TYPE>(x*s, y*s, z*s);
}

// Dot product and Cross product.
template<class V_TYPE>
V_TYPE Vector3D<V_TYPE>::operator*(const Vector3D<V_TYPE>& v) const {
    return (V_TYPE)(x*v.x + y*v.y + z*v.z);
}

template<class V_TYPE>
Vector3D<V_TYPE> Vector3D<V_TYPE>::cross(const Vector3D& v) const {
    return Vector3D<V_TYPE>(y*v.z - z*v.y,
                            z*v.x - x*v.z,
                            x*v.y - y*v.x);
}

// Copy constructor.
template<class V_TYPE>
Vector3D<V_TYPE>& Vector3D<V_TYPE>::operator=(const Vector3D<V_TYPE>& v) {
    if (&v != this)
        x = v.x; y = v.y, z = v.z;
    return *this;
}

// Normalizations.
template<class V_TYPE>
double Vector3D<V_TYPE>::normal() const {
    return sqrt((double)x*x + (double)y*y + (double)z*z);
}

template<class V_TYPE>
void Vector3D<V_TYPE>::normalize() {
    V_TYPE n = normal();
    x /= n;
    y /= n;
    z /= n;
}



void getNormalVector2fv(
        GLfloat x1, GLfloat y1, GLfloat z1, 
        GLfloat x2, GLfloat y2, GLfloat z2,
        GLfloat* nv);

void getNormalVector3f(
        GLfloat x1, GLfloat y1, GLfloat z1, 
        GLfloat x2, GLfloat y2, GLfloat z2,
        GLfloat x3, GLfloat y3, GLfloat z3,
        GLfloat* nv);

void getNormalVector3fv(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat* nv);
void getAvgVector4f(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat v4[], GLfloat* v);


#endif
