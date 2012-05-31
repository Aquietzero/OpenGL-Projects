#ifndef CONST_H
#define CONST_H

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cmath>

#define PI 3.1415926

using namespace std;

inline GLfloat radians(GLfloat x) { return x*PI/180.0; };

void setupRC();
void setupLightAndMaterial();
void setupTexture();

void setupTerrain();
void renderScene();

#endif
