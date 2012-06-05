#include "const.h"
#include "terrain.h"
#include "camera/camera.h"
#include "tree/tree.h"
#include "water.h"
#include "sky.h"
#include "glm/glm.h"
#include "glm/nv_math.h"
#include "glm/nv_algebra.h"

// Generate
Terrain *terrain;
Water   *water;
Sky     *sky;

// Load in
char castleOBJ[] = "obj/Palma/Palma.obj";
GLMmodel *castle = NULL;

Vector3D<GLfloat> cameraPos(2.0, 4.0, 6.0);
Vector3D<GLfloat> cameraViewDirection(-2.0, -2.0, -8.0);
Vector3D<GLfloat> upDirection(0.0, 1.0, 0.0);

Camera3D camera(cameraPos, cameraViewDirection, upDirection);
const GLint FPS = 15;

void setupTerrain() {

    terrain = new Terrain(256, 3.0, 1.2);
    srand(unsigned(time(NULL)));
    terrain->generate();

}

void setupWater() {

    water = new Water(32, 2.0, 1.3);

}

void setupSky() {
    
    sky = new Sky();

}

void setupOBJ() {

    castle = glmReadOBJ(castleOBJ);
    if (!castle) exit(0);
    glmUnitize(castle);
    glmFacetNormals(castle);
    glmVertexNormals(castle, 90.0);

}

void setupObjects() {

    setupTerrain();
    setupWater();
    setupOBJ();

}

void renderScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.render();

    GLfloat color[3] = {0.5, 0.5, 0.5};

    glBindTexture(GL_TEXTURE_2D, 3);
    glPushMatrix();
    sky->render(8);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 2);
    glPushMatrix();
    water->render(10, color, Water::SOLID);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    terrain->render(8, color, Terrain::SOLID);
    glPopMatrix();

    glPushMatrix();
    // glTranslatef(-8 + 16.0/256*20, terrain->terrain[20][15], -8 + 16.0/256*15);
    glmDraw(castle, GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();

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
            // camera.moveForward(0.1);
            camera.moveForwardDirection();
            break;
        case 's':
            //camera.moveBackward(0.1);
            camera.moveBackwardDirection();
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
    setupObjects();
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(keyDown);
    glutTimerFunc(1000.0/FPS, waving, 1);

    glutMainLoop();
    return 0;

}
