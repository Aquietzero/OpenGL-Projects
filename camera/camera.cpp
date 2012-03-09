#include "camera.h"

const Vector3D<GLfloat> Camera3D::FRONT = Vector3D<GLfloat>(0, 0, -1.0);
const Vector3D<GLfloat> Camera3D::BACK = Vector3D<GLfloat>(0, 0, 1.0);
const Vector3D<GLfloat> Camera3D::UP = Vector3D<GLfloat>(0, 1.0, 0);
const Vector3D<GLfloat> Camera3D::DOWN = Vector3D<GLfloat>(0, -1.0, 0);
const Vector3D<GLfloat> Camera3D::LEFT = Vector3D<GLfloat>(-1.0, 0, 0);
const Vector3D<GLfloat> Camera3D::RIGHT = Vector3D<GLfloat>(1.0, 0, 0);

const Vector3D<GLfloat> Camera3D::POSITION = Vector3D<GLfloat>(0, 0, 0.0);
const Vector3D<GLfloat> Camera3D::VIEW_DIRECTION = Vector3D<GLfloat>(0, 0, -1.0);
const Vector3D<GLfloat> Camera3D::ROTATION = Vector3D<GLfloat>(0, 0, 0);

Camera3D::Camera3D(Vector3D<GLfloat> pos, Vector3D<GLfloat> viewDir, Vector3D<GLfloat> upDir)
    : position(pos), viewDirection(viewDir), upDirection(upDir) {
    
    rotation = ROTATION;
    rightDirection = RIGHT;

}

void Camera3D::render() {

    Vector3D<GLfloat> viewPtr = position + viewDirection;

    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z,
              viewPtr.x, viewPtr.y, viewPtr.z,
              upDirection.x, upDirection.y, upDirection.z);

}

void Camera3D::move(Vector3D<GLfloat> direction) {
    position = position + direction;
}

void Camera3D::moveUp(float distance) {
    position = position + UP * distance;
}

void Camera3D::moveDown(float distance) {
    position = position + DOWN * distance;
}

void Camera3D::moveLeft(float distance) {
    position = position + LEFT * distance;
}

void Camera3D::moveRight(float distance) {
    position = position + RIGHT * distance;
}

void Camera3D::moveForward(float distance) {
    position = position + FRONT * distance;
}

void Camera3D::moveBackward(float distance) {
    position = position + BACK * distance;
}

/*
void Camera3D::rotateX(float degrees) {
    rotation.x += radians(degrees);
    viewDirection = viewDirection*cos(radians(degrees) +
                    upDirection*sin(radians(degrees)));
    upDirection = viewDirection.cross(rightDirection)*(-1);
}
*/

void Camera3D::rotateY(float degrees) {
    rotation.y += radians(degrees);
    viewDirection = viewDirection*((GLfloat)cos(radians(degrees))) -
                    rightDirection*((GLfloat)sin(radians(degrees)));
    viewDirection.normalize();
    rightDirection = viewDirection.cross(upDirection);
}

/*
void Camera3D::rotateZ(float degrees) {
    rotation.z += radians(degrees);
    rightDirection = rightDirection*cos(radians(degrees) +
                     upDirection*sin(radians(degrees)));
    upDirection = viewDirection.cross(rightDirection)*(-1);
}
*/
