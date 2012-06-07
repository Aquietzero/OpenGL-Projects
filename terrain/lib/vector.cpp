#include "vector.h"

/* Calculates the normal vector from the two given vectors according
 * to the cross product.
 */
void getNormalVector2fv(
        GLfloat x1, GLfloat y1, GLfloat z1,
        GLfloat x2, GLfloat y2, GLfloat z2,
        GLfloat* nv) {

    nv[0] = (y1*z2 - z1*y2);
    nv[1] = (z1*x2 - x1*z2);
    nv[2] = (x1*y2 - y1*x2);

    GLfloat length = sqrt(nv[0]*nv[0] + nv[1]*nv[1] + nv[2]*nv[2]);

    nv[0] /= length;
    nv[1] /= length;
    nv[2] /= length;

}
/*  
GLfloat* getNormalVector2f(
        GLfloat x1, GLfloat y1, GLfloat z1,
        GLfloat x2, GLfloat y2, GLfloat z2) {

    GLfloat *nv = new GLfloat[3];
    *//*  
    GLfloat length = sqrt((x1-x2) * (x1-x2) +
                          (y1-y2) * (y1-y2) +
                          (z1-z2) * (z1-z2));
    *//*

    nv[0] = (y1*z2 - z1*y2);
    nv[1] = (z1*x2 - x1*z2);
    nv[2] = (x1*y2 - x1*y2);

    GLfloat length = sqrt(nv[0]*nv[0] + nv[1]*nv[1] + nv[2]*nv[2]);

    nv[0] /= length;
    nv[1] /= length;
    nv[2] /= length;

    return nv;

}
*/
/* Calculates the normal vector from the three given points according
 * to the cross product.
 */
void getNormalVector3f(
        GLfloat x1, GLfloat y1, GLfloat z1,
        GLfloat x2, GLfloat y2, GLfloat z2,
        GLfloat x3, GLfloat y3, GLfloat z3,
        GLfloat* nv) {

    GLfloat v1[] = {x2-x1, y2-y1, z2-z1};
    GLfloat v2[] = {x3-x2, y3-y2, z3-z2};

    getNormalVector2fv(v2[0], v2[1], v2[2],
                       v1[0], v1[1], v1[2],
                       nv);
}
/* 
GLfloat* getNormalVector3f(
        GLfloat x1, GLfloat y1, GLfloat z1,
        GLfloat x2, GLfloat y2, GLfloat z2,
        GLfloat x3, GLfloat y3, GLfloat z3) {

    GLfloat v1[] = {x2-x1, y2-y1, z2-z1};
    GLfloat v2[] = {x2-x3, y2-y3, z2-z3};

    return getNormalVector2f(v2[0], v2[1], v2[2],
                             v1[0], v1[1], v1[2]);

}
*/

void getNormalVector3fv(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat* nv) {

    getNormalVector3f(v1[0], v1[1], v1[2],
                      v2[0], v2[1], v2[2],
                      v3[0], v3[1], v3[2],
                      nv);

}
/*
GLfloat* getNormalVector3fv(GLfloat v1[], GLfloat v2[], GLfloat v3[]) {

    return getNormalVector3f(v1[0], v1[1], v1[2],
                             v2[0], v2[1], v2[2],
                             v3[0], v3[1], v3[2]);

}
*/

void getAvgVector4f(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat v4[], GLfloat* v) {

    v[0] = AVG4(v1[0], v2[0], v3[0], v4[0]);
    v[1] = AVG4(v1[1], v2[1], v3[1], v4[1]);
    v[2] = AVG4(v1[2], v2[2], v3[2], v4[2]);

    GLfloat length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    
    v[0] /= length;
    v[1] /= length;
    v[2] /= length;

}
/* 
GLfloat* getAvgVector4f(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat v4[]) {

    GLfloat *v = new GLfloat[3];

    v[0] = AVG4(v1[0], v2[0], v3[0], v4[0]);
    v[1] = AVG4(v1[1], v2[1], v3[1], v4[1]);
    v[2] = AVG4(v1[2], v2[2], v3[2], v4[2]);

    GLfloat length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    
    v[0] /= length;
    v[1] /= length;
    v[2] /= length;

    return v;

}
*/
