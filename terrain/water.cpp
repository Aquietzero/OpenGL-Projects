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

    waterVertexNormals = new float**[size+1];
    waterPlaneNormals = new float**[size+1];

    for (int i = 0; i <= size; ++i) {
        water[i]        = new float[size+1];
        waveFunc[i]     = new float[size+1];
        waterPrev[i]    = new float[size+1];
        waveFuncPrev[i] = new float[size+1];
        waterVertexNormals[i] = new float*[size+1];
        waterPlaneNormals[i] = new float*[size+1];
        
        for (int j = 0; j <= size; ++j) {
            water[i][j]        = 0.0;
            waveFunc[i][j]     = 0.0;
            waterPrev[i][j]    = 0.0;
            waveFuncPrev[i][j] = 0.0;
            waterVertexNormals[i][j] = new float[3];
            waterPlaneNormals[i][j] = new float[3];
            waterVertexNormals[i][j][0] = 0.0;
            waterVertexNormals[i][j][1] = 1.0;
            waterVertexNormals[i][j][2] = 0.0;
            waterPlaneNormals[i][j][0] = 0.0;
            waterPlaneNormals[i][j][1] = 1.0;
            waterPlaneNormals[i][j][2] = 0.0;
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

    for (int i = 0; i <= size; ++i) {
        delete [] water[i];
        delete [] waterPrev[i];
        delete [] waveFunc[i];
        delete [] waveFuncPrev[i];
        for (int j = 0; j <= size; ++j) {
            delete[] waterVertexNormals[i][j];
            delete[] waterPlaneNormals[i][j];
        }
        delete[] waterVertexNormals[i];
        delete[] waterPlaneNormals[i];
            
    }

    delete [] water;
    delete [] waterPrev;
    delete [] waveFunc;
    delete [] waveFuncPrev;
    delete[] waterVertexNormals;
    delete[] waterPlaneNormals;

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

void Water::render(int s, GLfloat sc[], GLfloat ec[], GLuint texture, RENDER_TYPE t) {

    switch(t) {
        case SOLID:
            renderSolidWater(s, sc, ec, texture);
            break;
        case WIRE:
            renderWireWater(s, sc);
            break;
        default:
            renderWireWater(s, sc);
            break;
    }

}

void Water::renderWireWater(int s, float c[]) {

    GLfloat step = (GLfloat)2*s / size;
    GLfloat x = -(GLfloat)s;
    GLfloat z = -(GLfloat)s;

    // glColor3fv(c);
    glColor3f(0, 0, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    for (int i = 1; i < size; ++i) {
        for (int j = 1; j < size; ++j) {

            glVertex3f(x-step, water[i-1][j-1], z-step);
            glVertex3f(x-step, water[i-1][j], z);
            glVertex3f(x, water[i][j], z);
            glVertex3f(x, water[i][j-1], z-step);

            z += step;
        }
        x += step;
        z = -(GLfloat)s;
    }
    glEnd();

}

void Water::renderSolidWater(int s, GLfloat sc[], GLfloat ec[], GLuint texture) {

    GLfloat step = (GLfloat)2*s / size;
    GLfloat x = -(GLfloat)s;
    GLfloat z = -(GLfloat)s;

    GLfloat color_step[4] = { 
        (ec[0]-sc[0])/size, 
        (ec[1]-sc[1])/size, 
        (ec[2]-sc[2])/size, 
        (ec[3]-sc[3])/size
    };

    glDisable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glColor4f(0.32, 0.40, 0.53, 0.75);
    //glColor4f(0.45, 0.55, 0.80, 0.8);

    // glColor3ub(200, 200, 200);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    for (int i = 1; i < size; ++i) {
        for (int j = 1; j < size; ++j) { 
            glColor4f(
                    sc[0] + color_step[0]*i,
                    sc[1] + color_step[1]*i,
                    sc[2] + color_step[2]*i,
                    sc[3] + color_step[3]*i
            );

            getNormalVector2fv(0,    water[i+1][j]-water[i][j], step,
                    step, water[i+1][j+1]-water[i+1][j],     0,
                    waterPlaneNormals[i][j]);

            getAvgVector4f(waterPlaneNormals[i-1][j-1],
                    waterPlaneNormals[i][j-1],
                    waterPlaneNormals[i-1][j],
                    waterPlaneNormals[i][j],
                    waterVertexNormals[i][j]);

            glNormal3fv(waterVertexNormals[i-1][j-1]);
            glVertex3f(x-step, water[i-1][j-1], z-step);

            glNormal3fv(waterVertexNormals[i-1][j]);
            glVertex3f(x-step, water[i-1][j], z);

            glNormal3fv(waterVertexNormals[i][j]);
            glVertex3f(x, water[i][j], z);

            glNormal3fv(waterVertexNormals[i][j-1]);
            glVertex3f(x, water[i][j-1], z-step);


            z += step;
        }
        x += step;
        z = -(GLfloat)s;
    }
    glEnd();    

    glDisable(GL_BLEND);

    glEnable(GL_CULL_FACE);

}

