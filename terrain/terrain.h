#ifndef TERRAIN_H
#define TERRAIN_H

#include "const.h"

// For normal vector calculation.
#include "lib/vector.h"
#include "lib/mathaux.h"

/* Class Terrain uses Diamond-Square algorithm to generate the 
 * terrain model. The data structure is simple as a two dimensional
 * array in which the height of every point of the terrain is
 * stored.
 *
 * Requisit:
 *  (1) The terrain must be a square.
 *  (2) The size of the terrain must be the power of 2 plus 1.
 */
class Terrain {

    // Public default attributes.
    public:
        static const int DEFAULT_SIZE  = 256;
        static const float DEFAULT_HEIGHT = 1.0;
        static const float DEFAULT_ROUGHNESS = 0.9;
        enum RENDER_TYPE{ SOLID, WIRE };

        // The size of the terrain.
        int size;

        // The max_height of the terrain.
        float max_height;

        // The roughness of the terrain describes how the fluctuation
        // decreases each time of the iteration.
        float roughness;

        // The 2-d array which stores the height of points of the terrain.
        float **terrain;

        // Auxiliary functions.
        inline float avg(float x1, float x2, float x3, float x4) { 
            return (x1 + x2 + x3 + x4) / 4.0; 
        };
        inline float getRandom(float min, float max) { 
            return min + rand()*(max-min)/RAND_MAX; 
        };

    public:

        Terrain(const int   size       = DEFAULT_SIZE, 
                const float max_height = DEFAULT_HEIGHT, 
                const float roughness  = DEFAULT_ROUGHNESS);
        ~Terrain();

        void generate();
        void diamond(int x, int y, int step, float roughness);
        void square(int x, int y, int step, float roughness);
        void smooth();

        Vector2D<GLfloat> perfectSpot();        

        void render(int size, float c[], RENDER_TYPE type=WIRE);
        void renderWireTerrain(int size, float color[]);
        void renderSolidTerrain(int size, float color[]);

};

#endif
