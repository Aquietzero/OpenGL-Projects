#include "const.h"
#include "terrain.h"
#include "camera/camera.h"
#include "tree/tree.h"
#include "water.h"
#include "sky.h"
#include "smoke.h"
#include "glm/glm.h"
#include "glm/nv_math.h"
#include "glm/nv_algebra.h"

// Generate
Terrain *terrain;
Water   *water;
Sky     *sky;

// Load in
char castleOBJ[] = "obj/castle.obj";
GLMmodel *castle = NULL;

Vector3D<GLfloat> cameraPos(2.0, 4.0, 6.0);
Vector3D<GLfloat> cameraViewDirection(-2.0, -2.0, -8.0);
Vector3D<GLfloat> upDirection(0.0, 1.0, 0.0);

Camera3D camera(cameraPos, cameraViewDirection, upDirection);
const GLint FPS = 15;

void setupTerrain() {

    terrain = new Terrain(256, 8.0, 1.2);
    srand(unsigned(time(NULL)));
    terrain->generate();
    terrain->setPlaneNormals(WORLD_SIZE);

}

void setupWater() {

    water = new Water(256, 3.0, 0.3);

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

    // Render terrain
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    // glTranslatef(-WORLD_SIZE/2.0, 0, -WORLD_SIZE/2.0);
    terrain->render(WORLD_SIZE, color, Terrain::SOLID);
    glPopMatrix();

    // Render sky
    glBindTexture(GL_TEXTURE_2D, 3);
    glPushMatrix();
    sky->render(WORLD_SIZE);
    glPopMatrix();

    // Render water
    glBindTexture(GL_TEXTURE_2D, 2);
    glPushMatrix();
    water->render(WORLD_SIZE + 2, color, Water::SOLID);
    glPopMatrix();

    // Render castle
    glPushMatrix();
    glTranslatef(15, 1.5, -35);
    glScalef(3, 3, 3);
    // glmDraw(castle, GLM_SMOOTH);
    //glmDraw(castle, GLM_SMOOTH | GLM_MATERIAL);
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
            camera.moveForwardDirection(0.1);
            break;
        case 's':
            //camera.moveBackward(0.1);
            camera.moveBackwardDirection(0.1);
            break;
        case 'r':
            camera.moveUp(0.1);
            break;
        case 'f':
            camera.moveDown(0.1);
            break;
        case 'j':
            camera.rotateX(1);
            break;
        case 'k':
            camera.rotateX(-1);
            break;
        case 'h':
            camera.rotateY(1);
            break;
        case 'l':
            camera.rotateY(-1);
            break;
        case 'q':
            camera.rotateZ(1);
            break;
        case 'e':
            camera.rotateZ(-1);
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
