#include "const.h"
#include "terrain.h"

Terrain *terrain;
GLfloat alpha, beta, radius;

void setupTerrain() {

    alpha = 30.0;
    beta = 0.0;
    radius = 8.0;

    terrain = new Terrain();
    srand(unsigned(time(NULL)));
    terrain->generateTerrain();

}

void renderScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3ub(150, 150, 150);

    glLoadIdentity();
    gluLookAt(radius*cos(radians(alpha))*sin(radians(beta)), 
              radius*sin(radians(alpha)), 
              radius*cos(radians(alpha))*cos(radians(beta)), 
              0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    GLfloat color[3] = {0.2, 0.2, 0.3};
    terrain->renderTerrain(4, color, terrain->WIRE);

    glutSwapBuffers();

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

void specialKeys(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT)
        beta += 2.0;
    if (key == GLUT_KEY_RIGHT)
        beta -= 2.0;
    if (key == GLUT_KEY_UP)
        alpha += 2.0;
    if (key == GLUT_KEY_DOWN)
        alpha -= 2.0;

    if (beta >= 360.0)
        beta = 0.0;

    glutPostRedisplay();

}

void spinning(int value) {

    if (beta <= 360.0)
        beta += 1.0;
    else
        beta = 1.0;

    glutPostRedisplay();
    glutTimerFunc(65, spinning, 1);

}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Terrain");

    setupRC();
    setupTerrain();
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutSpecialFunc(specialKeys);
    //glutTimerFunc(65, spinning, 1);

    glutMainLoop();
    return 0;

}
