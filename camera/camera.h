#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <iostream>
#include <math.h>

#include "lib/mathaux.h"
#include "lib/vector.h"

using namespace std;

class Camera3D {

    // default direction normal vectors
    static const Vector3D<GLfloat> FRONT;
    static const Vector3D<GLfloat> BACK;
    static const Vector3D<GLfloat> UP;
    static const Vector3D<GLfloat> DOWN;
    static const Vector3D<GLfloat> LEFT;
    static const Vector3D<GLfloat> RIGHT;

    // default camera attribute vectors
    static const Vector3D<GLfloat> POSITION;
    static const Vector3D<GLfloat> VIEW_DIRECTION;
    static const Vector3D<GLfloat> ROTATION;

    private:
        Vector3D<GLfloat> position;
        Vector3D<GLfloat> viewDirection;
        Vector3D<GLfloat> rotation;
        Vector3D<GLfloat> upDirection;
        Vector3D<GLfloat> rightDirection;

    public:
        Camera3D();
        Camera3D(Vector3D<GLfloat> pos,
               Vector3D<GLfloat> viewDir,
               Vector3D<GLfloat> upDir);
        ~Camera3D() {};

        void render();

        void rotate(Vector3D<GLfloat>);
        void rotateX(float);
        void rotateY(float);
        void rotateZ(float);
        
        void move(Vector3D<GLfloat>);
        void moveUp(float);
        void moveDown(float);
        void moveLeft(float);
        void moveRight(float);
        void moveForward(float);
        void moveBackward(float);

};

#endif
