#include "vector.h"

/* Calculates the normal vector from the two given vectors according
 * to the cross product.
 */
GLfloat* getNormalVector(
        GLfloat x1, GLfloat y1, GLfloat z1,
        GLfloat x2, GLfloat y2, GLfloat z2) {

    GLfloat *nv = new GLfloat[3];
    GLfloat length = sqrt((x1-x2) * (x1-x2) +
                          (y1-y2) * (y1-y2) +
                          (z1-z2) * (z1-z2));

    nv[0] = (y1*z2 - z1*y2) / length;
    nv[1] = (z1*x2 - x1*z2) / length;
    nv[2] = (x1*y2 - x1*y2) / length;

    return nv;

}
