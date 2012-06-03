#include "const.h"
#include "terrain.h"
#include "camera/camera.h"
#include "tree/tree.h"
#include "water.h"

Terrain *terrain;
Water *water;
FractalTree *tree1;
FractalTree *tree2;

Vector3D<GLfloat> cameraPos(2.0, 4.0, 6.0);
Vector3D<GLfloat> cameraViewDirection(-2.0, -2.0, -8.0);
Vector3D<GLfloat> upDirection(0.0, 1.0, 0.0);

Camera3D camera(cameraPos, cameraViewDirection, upDirection);
const GLint FPS = 15;

void setupTerrain() {

    terrain = new Terrain(256, 2.0, 1.2);
    srand(unsigned(time(NULL)));
    terrain->generate();

}

void setupWater() {

    water = new Water(32, 2.0, 1.3);

}

void setupTree() {

    tree1 = new FractalTree(50, 0.7, 0.5, 0.03, 3);
    tree1->generate(1.0, 0.2, 0, 0, 0, 0);

    tree2 = new FractalTree(50, 0.7, 0.5, 0.03, 3);
    tree2->generate(0.6, 0.2, 0, 0, 0, 0);

}

void renderScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.render();

    GLfloat color[3] = {0.5, 0.5, 0.5};
    glBindTexture(GL_TEXTURE_2D, 2);
    water->render(8, color, Water::SOLID);
    glBindTexture(GL_TEXTURE_2D, 1);
    terrain->render(8, color, Terrain::SOLID);

    /*  
    glPushMatrix();
    glTranslatef(-4 + 8.0/256*20, terrain->terrain[20][15], -4 + 8.0/256*15);
    tree1->render();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4 + 8.0/256*50, terrain->terrain[50][35], -4 + 8.0/256*35);
    tree2->render();
    glPopMatrix();
    */

    /*
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0, 0, 1.0, 0.8);
    glBegin(GL_QUADS);
        glVertex3f(-40.0, 0.0, -40.0);
        glVertex3f(-40.0, 0.0,  40.0);
        glVertex3f( 40.0, 0.0,  40.0);
        glVertex3f( 40.0, 0.0, -40.0);
    glEnd();
    glDisable(GL_BLEND);
    */

    glutSwapBuffers();

}

void changeSize(GLsizei w, GLsizei h) {

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glFrustum(-1.0, 1.0, -1.0*h/w, 1.0*h/w, 1.5, 100.0);
    else
        glFrustum(-1.0*w/h, 1.0*w/h, -1.0, 1.0, 1.5, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void waving(int value) {

    water->wave();
    glutPostRedisplay();
    glutTimerFunc(1000.0/FPS, waving, 1);

}

void keyDown(unsigned char key, int x, int y) {

    switch(key) {
        case 'w':
            camera.moveForward(0.1);
            break;
        case 's':
            camera.moveBackward(0.1);
            break;
        case 'r':
            camera.moveUp(0.1);
            break;
        case 'f':
            camera.moveDown(0.1);
            break;
        case 'j':
            camera.rotateX(0.5);
            break;
        case 'k':
            camera.rotateX(-0.5);
            break;
        case 'h':
            camera.rotateY(0.5);
            break;
        case 'l':
            camera.rotateY(-0.5);
            break;
        case 'q':
            camera.rotateZ(0.5);
            break;
        case 'e':
            camera.rotateZ(-0.5);
            break;

    }

    glutPostRedisplay();

}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Terrain");

    setupRC();
    setupTerrain();
    setupTree();
    setupWater();
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(keyDown);
    glutTimerFunc(1000.0/FPS, waving, 1);

    glutMainLoop();
    return 0;

}
