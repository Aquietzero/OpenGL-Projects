#include <GL/glut.h>
#include <iostream>

using namespace std;

GLfloat nRange = 2.0f;
GLint xWindow = 500;
GLint yWindow = 500;

GLfloat reStep, imStep;
GLfloat reInit, imInit, reMax, imMax;
GLint iterMax;

GLfloat reC;
GLfloat imC;

void setupMandelbrot() {

    reStep = (2.0f * nRange) / xWindow;
    imStep = (2.0f * nRange) / yWindow;

    reInit = -2.0f;
    imInit = -2.0f;
    reMax = 2.0f;
    imMax = 2.0f;

    iterMax = 50;
    reC = 0.2f;
    imC = 0.5f;

}

void renderMandelbort() {

    GLfloat re, im;
    GLboolean isInside;
    GLfloat r, i, r_prev, i_prev;
    int n;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (int x = 0; x < xWindow; ++x) {

        re = reInit + (GLfloat)x * reStep;
        for (int y = 0; y < yWindow; ++y) {

            isInside = true;
            im = imInit + (GLfloat)y * imStep;

            r_prev = re, i_prev = im;
            for (n = 0; n < iterMax; ++n) {
                r = r_prev*r_prev - i_prev*i_prev + reC;
                i = 2*r_prev*i_prev + imC;

                r_prev = r;
                i_prev = i;

                if (r*r + i*i > 4.0f) {
                    isInside = false;
                    break;
                }
            }

            if (isInside) {
                glVertex2f(re, im);
                glColor3ub(0, 0, 0);
            }
            else {
                glColor3f(0.0f*n/iterMax, 0, 0.8f*n/iterMax);
                glVertex2f(re, im);
            }
        }
    }
    glEnd();

    glutSwapBuffers();

}

void setupRC() {

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    setupMandelbrot();

}

void changeSize(GLsizei w, GLsizei h) {

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else
        glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // redisplay the julia set when the window is reshaped.
    xWindow = w;
    yWindow = h;
    setupMandelbrot();
    glutPostRedisplay();

}

void specialKeys(int key, int x, int y) {

    if (key == GLUT_KEY_UP)
        reC += 0.01f;
    if (key == GLUT_KEY_DOWN)
        reC -= 0.01f;

    glutPostRedisplay();

}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(xWindow, yWindow);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Mandelbrot Set");

    setupRC();
    glutDisplayFunc(renderMandelbort);
    glutReshapeFunc(changeSize);
    glutSpecialFunc(specialKeys);

    glutMainLoop();

    return 0;

}
