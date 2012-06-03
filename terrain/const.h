#pragma once

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

#define TEXTURE_COUNT  2
#define GROUND_TEXTURE 0
#define WATER_TEXTURE  1
#define GROUND_TEXTURE_SRC "textures/sand.bmp"
#define WATER_TEXTURE_SRC  "textures/water.bmp"

static GLuint textures[TEXTURE_COUNT];
static const char *textures_src[TEXTURE_COUNT] = {GROUND_TEXTURE_SRC, WATER_TEXTURE_SRC};

using namespace std;

inline GLfloat radians(GLfloat x) { return x*PI/180.0; };

void setupRC();
void setupLightAndMaterial();
void setupTexture();

void setupTerrain();
void renderScene();

#endif
