#include "camera.h"

const Vector3D<GLfloat> Camera::FRONT = Vector3D<GLfloat>(0, 0, -1.0);
const Vector3D<GLfloat> Camera::BACK = Vector3D<GLfloat>(0, 0, 1.0);
const Vector3D<GLfloat> Camera::UP = Vector3D<GLfloat>(0, 1.0, 0);
const Vector3D<GLfloat> Camera::DOWN = Vector3D<GLfloat>(0, -1.0, 0);
const Vector3D<GLfloat> Camera::LEFT = Vector3D<GLfloat>(-1.0, 0, 0);
const Vector3D<GLfloat> Camera::RIGHT = Vector3D<GLfloat>(1.0, 0, 0);

const Vector3D<GLfloat> Camera::POSITION = Vector3D<GLfloat>(0, 0, 5.0);
const Vector3D<GLfloat> Camera::VIEW_DIRECTION = Vector3D<GLfloat>(0, 0, -5.0);
const Vector3D<GLfloat> Camera::ROTATION = Vector3D<GLfloat>(0, 0, 0);

Camera::Camera(Vector3D<GLfloat> pos, Vector3D<GLfloat> viewDir, Vector3D<GLfloat> upDir)
    : position(pos), viewDirection(viewDir), upDirection(upDir) {
    
    rotation = ROTATION;
    rightDirection = RIGHT;

}

void Camera::render() {

    Vector3D<GLfloat> viewPtr = position + viewDirection;

    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z,
              viewPtr.x, viewPtr.y, viewPtr.z,
              upDirection.x, upDirection.y, upDirection.z);

}

void Camera::move(Vector3D<GLfloat> direction) {
    position = position + direction;
}

void Camera::moveUp(float distance) {
    position = position + UP * distance;
}

void Camera::moveDown(float distance) {
    position = position + DOWN * distance;
}

void Camera::moveLeft(float distance) {
    position = position + LEFT * distance;
}

void Camera::moveRight(float distance) {
    position = position + RIGHT * distance;
}

void Camera::moveForward(float distance) {
    position = position + FRONT * distance;
}

void Camera::moveBackward(float distance) {
    position = position + BACK * distance;
}
