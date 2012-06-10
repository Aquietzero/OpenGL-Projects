/*
 * =====================================================================================
 *
 *       Filename:  water.h
 *
 *    Description:  The definition of water
 *
 *        Version:  1.0
 *        Created:  05/31/2012 09:32:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef WATER_H
#define WATER_H

#include "const.h"
#include "terrain.h"

class Water {

    // Public default attributes.
    public:
        static const int   DEFAULT_SIZE  = 256;
        static const float DEFAULT_HEIGHT = 1.0;
        static const float DEFAULT_ROUGHNESS = 0.9;
        enum RENDER_TYPE{ SOLID, WIRE };

        // The size of the water surface.
        int size;

        // The 2-d array which stores the heights of the water.
        float **water;
        float **waterPrev;
        float ***waterVertexNormals;
        float ***waterPlaneNormals;
        // The 2-d array which stores the waving function.
        float **waveFunc;
        float **waveFuncPrev;

    public:

        Water(const int   size       = DEFAULT_SIZE, 
              const float max_height = DEFAULT_HEIGHT, 
              const float roughness  = DEFAULT_ROUGHNESS);
        ~Water();

        void generate();
        void wave();

        void render(int size, GLfloat sc[], GLfloat ec[], GLuint texture, RENDER_TYPE type=WIRE);
        void renderWireWater(int size, float color[]);
        void renderSolidWater(int size, GLfloat sc[], GLfloat ec[], GLuint texture);

};

#endif
