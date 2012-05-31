/*
 * =====================================================================================
 *
 *       Filename:  tree.h
 *
 *    Description:  tree.h defines a random fractal tree drawer.
 *
 *        Version:  1.0
 *        Created:  05/24/2012 09:52:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef FRACTAL_TREE
#define FRACTAL_TREE

#include "const.h"
#include <iostream>

#define DEFAULT_ANGLE_VARIATION  50
#define DEFAULT_LENGTH_FACTOR    0.7
#define DEFAULT_THICKNESS_FACTOR 0.5
#define DEFAULT_MIN_TRUNK_LENGTH 0.2
#define DEFAULT_SUBTREES_NUM     4

using namespace std;

class FractalTree {

    public:
        static GLfloat angleVariation;
        static GLfloat lengthFactor;
        static GLfloat thicknessFactor;
        static GLfloat minTrunkLength;
        static GLint   subtreesNum;

    private:
        GLfloat trunkLength; 
        GLfloat trunkThickness; 

        GLfloat thetaX, thetaY, thetaZ;
        GLfloat posY;

        FractalTree **subtrees;

    public:
        FractalTree(
            GLfloat angleV     = DEFAULT_ANGLE_VARIATION,
            GLfloat lengthF    = DEFAULT_LENGTH_FACTOR,
            GLfloat thicknessF = DEFAULT_THICKNESS_FACTOR,
            GLfloat minTrunkL  = DEFAULT_MIN_TRUNK_LENGTH,
            GLint   subtreesN  = DEFAULT_SUBTREES_NUM);
        ~FractalTree() {}
        void generate(
            GLfloat trunkLength, 
            GLfloat trunkThickness, 
            GLfloat posY,
            GLfloat thetaX,
            GLfloat thetaY,
            GLfloat thetaZ
        );
        void render();

};

#endif
