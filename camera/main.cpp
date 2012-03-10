#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <cmath>
#include "lib/vector.h"
#include "camera.h"

#define PI 3.1415926

//GLfloat alpha;
//GLfloat beta;
//GLfloat radius;
Camera3D camera;

GLfloat radians(GLfloat d) {
    return d*PI/180.0;
}

void renderScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.5, 0.5, 0.5);

    camera.render();
    glPushMatrix();

    glTranslatef(0, 0, -5.0);
    glutSolidCube(1.0);

    glPopMatrix();

    glutSwapBuffers();

}

void setupRC() {

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    GLfloat ambientLight[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat diffuseLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightSource[] = {4.0, 4.0, 4.0, 1.0};

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightSource);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

}

void changeSize(GLsizei w, GLsizei h) {


    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glFrustum(-1.0, 1.0, -1.0*h/w, 1.0*h/w, 1.5, 20.0);
    else
        glFrustum(-1.0*w/h, 1.0*w/h, -1.0, 1.0, 1.5, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void keyDown(unsigned char key, int x, int y) {

    switch(key) {
        case 'w':
            camera.moveForward(0.1);
            break;
        case 's':
            camera.moveBackward(0.1);
            break;
        case 'a':
            camera.moveLeft(0.1);
            break;
        case 'd':
            camera.moveRight(0.1);
            break;
        case 'q':
            camera.rotateY(0.5);
            break;
        case 'e':
            camera.rotateY(-0.5);
    }

    glutPostRedisplay();
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Camera Demo");

    setupRC();
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(keyDown);

    glutMainLoop();
    return 0;

}
