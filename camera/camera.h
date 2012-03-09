#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <math.h>

#include "lib/mathaux.h"
#include "lib/vector.h"

class Camera {

    const Vector3D<GLfloat> DEFAULT_POSITION = Vector3D<GLfloat>(0.0, 0.0, 0.0);
    const Vector3D<GLfloat> DEFAULT_LOOKAT   = Vector3D<GLfloat>(0.0, 0.0, -1.0);
    const Vector3D<GLfloat> DEFAULT_ROTATION = Vector3D<GLfloat>(0.0, 0.0, 0.0);

    private:
        Vector3D<GLfloat> position;
        Vector3D<GLfloat> lookAt;
        Vector3D<GLfloat> rotation;

    public:
        Camera(Vector3D<GLfloat> position = DEFAULT_POSITION,
               Vector3D<GLfloat> lookAt   = DEFAULT_LOOKAT,
               Vector3D<GLfloat> rotation = DEFAULT_ROTATION);
        ~Camera() {};

        void render();
        void rotateX(float radians);
        void rotateY(float radians);
        void rotateZ(float radians);
        void move(float distance);
};

#endif
