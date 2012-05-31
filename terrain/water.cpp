/*
 * =====================================================================================
 *
 *       Filename:  water.cpp
 *
 *    Description:  Implementation of class water.
 *
 *        Version:  1.0
 *        Created:  05/31/2012 09:46:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "water.h"

Water::Water(const int s, const float max_h, const float r) {

    size = isPowerOf2(s) ? s : closestPowerOf2lt(s);

    // Allocate the water and waveFunc.
    water = new float*[size+1];
    waveFunc = new float*[size+1];
    for (int i = 0; i <= size; ++i) {
        water[i] = new float[size+1];
        waveFunc[i] = new float[size+1];
    }

    for (int i = 0; i <= size; ++i)
        for (int j = 0; j <= size; ++j) {
            water[i][j] = 0.0;
            waveFunc[i][j] = 0.0;
        }

    // Using the water generator to randomly generate a wave
    // function for water.
    Terrain *t = new Terrain(size, max_h, r);
    srand(unsigned(time(NULL)));
    t->generate();

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            waveFunc[i][j] = t->terrain[i][j];

}


Water::~Water() {

    delete [] water;

}

void Water::wave() {

    GLfloat sum;
    GLint ig, il, jg, jl;
    GLfloat t = 0.1;
    GLfloat c = 2;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            il = i == 0 ? size - 1 : i - 1;
            ig = i == size - 1 ? 0 : i + 1;
            jl = j == 0 ? size - 1 : j - 1;
            jg = j == size - 1 ? 0 : j + 1;

            sum = waveFunc[ig][j] +
                  waveFunc[il][j] +
                  waveFunc[i][jg] +
                  waveFunc[i][jl] -
                  4 * waveFunc[i][j];
            sum = sum * t * c * c / 25.0;

            water[i][j] += sum;
            waveFunc[i][j] += t * water[i][j];
        }
    }

}

void Water::render(int s, float c[], RENDER_TYPE t) {

    switch(t) {
        case SOLID:
            renderSolidWater(s, c);
            break;
        case WIRE:
            renderWireWater(s, c);
            break;
        default:
            renderWireWater(s, c);
            break;
    }

}

void Water::renderWireWater(int s, float c[]) {

    GLfloat step = (GLfloat)2*s / size;
    GLfloat x = -(GLfloat)s;
    GLfloat y = -(GLfloat)s;
    GLfloat *nv;

    glColor3fv(c);

    glBegin(GL_LINES);
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            nv = getNormalVector2f(step, water[i+1][j]-water[i][j], 0,
                                 0, water[i+1][j]-water[i+1][j+1], step);
            glNormal3fv(nv);

            glVertex3f(x, water[i][j], y);
            glVertex3f(x, water[i][j+1], y+step);

            glVertex3f(x, water[i][j+1], y+step);
            glVertex3f(x+step, water[i+1][j+1], y+step);

            glVertex3f(x+step, water[i+1][j+1], y+step);
            glVertex3f(x+step, water[i+1][j], y);

            glVertex3f(x+step, water[i+1][j], y);
            glVertex3f(x, water[i][j], y);
            y += step;
        }
        x += step;
        y = -(GLfloat)s;
    }
    glEnd();

}

void Water::renderSolidWater(int s, float c[]) {

    GLfloat step = (GLfloat)2*s / size;
    GLfloat x = -(GLfloat)s;
    GLfloat z = -(GLfloat)s;
    GLfloat *nv;

    glColor3fv(c);

    glBegin(GL_QUADS);
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            nv = getNormalVector2f(0, water[i+1][j]-water[i][j], step,
                                   step, water[i+1][j]-water[i+1][j+1], 0);
            glNormal3fv(nv);
            glTexCoord2f((float)i/size, (float)j/size);
            glVertex3f(x, water[i][j], z);
            glTexCoord2f((float)i/size, (float)(j+1)/size);
            glVertex3f(x, water[i][j+1], z+step);
            glTexCoord2f((float)(i+1)/size, (float)(j+1)/size);
            glVertex3f(x+step, water[i+1][j+1], z+step);
            glTexCoord2f((float)(i+1)/size, (float)j/size);
            glVertex3f(x+step, water[i+1][j], z);

            z += step;
        }
        x += step;
        z = -(GLfloat)s;
    }
    glEnd();

}
