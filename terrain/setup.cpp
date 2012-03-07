#include "const.h"

void setupRC() {

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    setupLight();
    setupMaterial();

}

void setupLight() {

    GLfloat ambientLight[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat diffuseLight[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat lightSource[]  = {5.0, 5.0, 5.0};

    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightSource);

}

void setupMaterial() {

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

}


