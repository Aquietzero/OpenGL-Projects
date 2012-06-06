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
    water        = new float*[size+1];
    waveFunc     = new float*[size+1];
    waterPrev    = new float*[size+1];
    waveFuncPrev = new float*[size+1];

    for (int i = 0; i <= size; ++i) {
        water[i]        = new float[size+1];
        waveFunc[i]     = new float[size+1];
        waterPrev[i]    = new float[size+1];
        waveFuncPrev[i] = new float[size+1];
        
        for (int j = 0; j <= size; ++j) {
            water[i][j]        = 0.0;
            waveFunc[i][j]     = 0.0;
            waterPrev[i][j]    = 0.0;
            waveFuncPrev[i][j] = 0.0;
        }
    }

    // Using the water generator to randomly generate a wave
    // function for water.
    Terrain *t = new Terrain(size, max_h, r);
    srand(unsigned(time(NULL)));
    t->generate();

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            waveFunc[i][j]     = t->terrain[i][j];
            waveFuncPrev[i][j] = t->terrain[i][j];
        }

}


Water::~Water() {

    for (int i = 0; i < size; ++i) {
        delete [] water[i];
        delete [] waterPrev[i];
        delete [] waveFunc[i];
        delete [] waveFuncPrev[i];
    }

    delete [] water;
    delete [] waterPrev;
    delete [] waveFunc;
    delete [] waveFuncPrev;

}

void Water::wave() {

    GLfloat sum;
    GLint ig, il, jg, jl;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            il = i == 0 ? size - 1 : i - 1;
            ig = i == size - 1 ? 0 : i + 1;
            jl = j == 0 ? size - 1 : j - 1;
            jg = j == size - 1 ? 0 : j + 1;

            sum = waveFuncPrev[ig][j] +
                  waveFuncPrev[il][j] +
                  waveFuncPrev[i][jg] +
                  waveFuncPrev[i][jl] -
                  4 * waveFuncPrev[i][j];
            sum = sum / 10.0;

            water[i][j] = waterPrev[i][j] + sum;
            waveFunc[i][j] = waveFuncPrev[i][j] + water[i][j];
        }
    }

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            waterPrev[i][j]    = water[i][j];
            waveFuncPrev[i][j] = waveFunc[i][j];
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

    // glColor3fv(c);
    glColor3ub(255, 255, 255);

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5, 0.5, 0.65, 0.9);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // glColor3ub(200, 200, 200);
    glBegin(GL_QUADS);
    for (int i = 1; i < size - 2; ++i) {
        for (int j = 1; j < size - 2; ++j) {

            glNormal3fv(getNormalVector(i, j, step, water));
            glVertex3f(x, water[i][j], z);

            glNormal3fv(getNormalVector(i, j+1, step, water));
            glVertex3f(x, water[i][j+1], z+step);
            
            glNormal3fv(getNormalVector(i+1, j+1, step, water));
            glVertex3f(x+step, water[i+1][j+1], z+step);

            glNormal3fv(getNormalVector(i+1, j, step, water));
            glVertex3f(x+step, water[i+1][j], z);

            z += step;
        }

        x += step;
        z = -(GLfloat)s;
    }

    glEnd();
    glDisable(GL_BLEND);

}

GLfloat* Water::getNormalVector(int i, int j, GLfloat step, GLfloat **water) {

    GLfloat *nv1, *nv2, *nv3, *nv4, *nvAvg;

    nv1 = getNormalVector2f(0, water[i+1][j]-water[i][j], step,
            step, water[i+1][j]-water[i+1][j+1], 0);

    nv2 = getNormalVector2f(0, water[i+1][j-1]-water[i][j-1], step,
            step, water[i+1][j-1]-water[i+1][j], 0);

    nv3 = getNormalVector2f(0, water[i][j-1]-water[i-1][j-1], step,
            step, water[i][j-1]-water[i][j], 0);

    nv4 = getNormalVector2f(0, water[i][j]-water[i-1][j], step,
            step, water[i][j]-water[i][j+1], 0);

    nvAvg = getAvgVector4f(nv1, nv2, nv3, nv4);

    return nvAvg;

}
