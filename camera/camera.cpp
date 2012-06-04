#include "camera.h"

const Vector3D<GLfloat> Camera3D::FRONT = Vector3D<GLfloat>(0, 0, -1.0);
const Vector3D<GLfloat> Camera3D::BACK  = Vector3D<GLfloat>(0, 0, 1.0);
const Vector3D<GLfloat> Camera3D::UP    = Vector3D<GLfloat>(0, 1.0, 0);
const Vector3D<GLfloat> Camera3D::DOWN  = Vector3D<GLfloat>(0, -1.0, 0);
const Vector3D<GLfloat> Camera3D::LEFT  = Vector3D<GLfloat>(-1.0, 0, 0);
const Vector3D<GLfloat> Camera3D::RIGHT = Vector3D<GLfloat>(1.0, 0, 0);

const Vector3D<GLfloat> Camera3D::POSITION       = Vector3D<GLfloat>(0, 0, 0);
const Vector3D<GLfloat> Camera3D::VIEW_DIRECTION = Vector3D<GLfloat>(0, 0, -1.0);
const Vector3D<GLfloat> Camera3D::ROTATION       = Vector3D<GLfloat>(0, 0, 0);

Camera3D::Camera3D() {

    position = Vector3D<GLfloat>(0, 0, 0);
    viewDirection = Vector3D<GLfloat>(0, 0, -1.0);
    rotation = Vector3D<GLfloat>(0, 0, 0);
    upDirection = Vector3D<GLfloat>(0, 1.0, 0);
    rightDirection = Vector3D<GLfloat>(-1.0, 0, 0);

}

Camera3D::Camera3D(Vector3D<GLfloat> pos, Vector3D<GLfloat> viewDir, Vector3D<GLfloat> upDir)
    : position(pos), viewDirection(viewDir), upDirection(upDir) {
    
    rotation = Vector3D<GLfloat>(0, 0, 0);
    rightDirection = viewDirection.cross(upDirection);
    rightDirection.normalize();

}

void Camera3D::render() {

    Vector3D<GLfloat> viewPtr = position + viewDirection;

    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z,
              viewPtr.x, viewPtr.y, viewPtr.z,
              upDirection.x, upDirection.y, upDirection.z);

    //cout << RIGHT.x << '\t' << RIGHT.y << '\t' << RIGHT.z << endl;
    //cout << position.x << '\t' << position.y << '\t' << position.z << endl;
    //cout << viewPtr.x << '\t' << viewPtr.y << '\t' << viewPtr.z << endl;

}

void Camera3D::move(Vector3D<GLfloat> direction) {
    position = position + direction;
}

void Camera3D::moveForwardDirection() {
    position = position + viewDirection * 0.05;
}

void Camera3D::moveBackwardDirection() {
    position = position - viewDirection * 0.05;
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

void Camera3D::rotate(Vector3D<GLfloat> degreeV) {
    rotateX(degreeV.x);
    rotateX(degreeV.y);
    rotateX(degreeV.z);
}

void Camera3D::rotateX(float degrees) {
    rotation.x += radians(degrees);
    viewDirection = viewDirection*((GLfloat)cos(radians(degrees))) +
                    upDirection*((GLfloat)sin(radians(degrees)));
    viewDirection.normalize();
    upDirection = viewDirection.cross(rightDirection)*(-1);
}

void Camera3D::rotateY(float degrees) {
    rotation.y += radians(degrees);
    viewDirection = viewDirection*((GLfloat)cos(radians(degrees))) -
                    rightDirection*((GLfloat)sin(radians(degrees)));
    viewDirection.normalize();
    rightDirection = viewDirection.cross(upDirection);
}

void Camera3D::rotateZ(float degrees) {
    rotation.z += radians(degrees);
    rightDirection = rightDirection*((GLfloat)cos(radians(degrees))) +
                     upDirection*((GLfloat)sin(radians(degrees)));
    rightDirection.normalize();
    upDirection = viewDirection.cross(rightDirection)*(-1);
}
