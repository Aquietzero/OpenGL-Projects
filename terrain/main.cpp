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
#include "lib/bmpReader.h"

// Textures
#define TEXTURE_COUNT   5
#define GROUND_TEXTURE  0
#define WATER_TEXTURE   1
#define SKY_TEXTURE     2
#define SAND_TEXTURE    3
#define SUNSET_TEXTURE  4

#define GROUND_TEXTURE_SRC "textures/ground3.bmp"
#define WATER_TEXTURE_SRC  "textures/water.bmp"
#define SKY_TEXTURE_SRC    "textures/sky6.bmp"
#define SAND_TEXTURE_SRC   "textures/sand.bmp"
#define SUNSET_TEXTURE_SRC "textures/sunset.bmp"

static GLuint textures[TEXTURE_COUNT];
static const char *textures_src[TEXTURE_COUNT] 
    = {GROUND_TEXTURE_SRC, WATER_TEXTURE_SRC, SKY_TEXTURE_SRC, SAND_TEXTURE_SRC, SUNSET_TEXTURE_SRC};

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

// show mode
Terrain::RENDER_TYPE terrain_mode = Terrain::SOLID;
Water::RENDER_TYPE   water_mode   = Water::SOLID;

void setupMode(int m) {

    switch(m) {
        case 1: 
            terrain_mode = Terrain::SOLID;
            break;
        case 2:
            terrain_mode = Terrain::WIRE;
            break;
        case 3:
            water_mode = Water::SOLID;
            break;
        case 4:
            water_mode = Water::WIRE;
    }

}

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

    // Render terrain
    glPushMatrix();
    GLfloat terrain_color[4] = { 0.2, 0.2, 0.45, 0.0 };
    terrain->render(WORLD_SIZE, terrain_color, textures[GROUND_TEXTURE], terrain_mode);
    glPopMatrix();

    // Render sky
    glPushMatrix();
    sky->render(WORLD_SIZE, textures[SKY_TEXTURE]);
    glPopMatrix();

    // Render water
    glPushMatrix();
    GLfloat water_color[4] = { 0.30, 0.40, 0.55, 0.8 };
    water->render(WORLD_SIZE + 2, water_color, textures[WATER_TEXTURE], water_mode);
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
            camera.moveForwardDirection(0.1);
            break;
        case 's':
            camera.moveBackwardDirection(0.1);
            break;
        case 'a':
            camera.moveLeft(1);
            break;
        case 'd':
            camera.moveRight(1);
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

void setupMenu() {

    int terrainModeMenu = glutCreateMenu(setupMode);
    glutAddMenuEntry("Solid", 1);
    glutAddMenuEntry("WIRE", 2);

    int waterModeMenu = glutCreateMenu(setupMode);
    glutAddMenuEntry("Solid", 3);
    glutAddMenuEntry("Wire", 4);

    int mainMenu = glutCreateMenu(setupMode);
    glutAddSubMenu("Terrain", terrainModeMenu);
    glutAddSubMenu("Water", waterModeMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void setupTexture() {

    GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glGenTextures(TEXTURE_COUNT, textures);
    for (GLint i = 0; i < TEXTURE_COUNT; ++i) {

        iWidth = 0;
        iHeight = 0;

        glBindTexture(GL_TEXTURE_2D, textures[i]);

        // Load texture
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        pBytes = bmpReader(textures_src[i], iWidth, iHeight);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, iWidth, iHeight, 
                0, GL_BGR, GL_UNSIGNED_BYTE, pBytes);

        GLfloat fLargest;

        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
        
        free(pBytes);

    }

}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Terrain");

    setupMenu();
    setupRC();
    setupTexture();
    setupObjects();
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(keyDown);
    glutTimerFunc(1000.0/FPS, waving, 1);

    glutMainLoop();
    return 0;

}
