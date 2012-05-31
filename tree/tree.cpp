/*
 * =====================================================================================
 *
 *       Filename:  tree.cpp
 *
 *    Description:  The implementation of the class tree.
 *
 *        Version:  1.0
 *        Created:  05/24/2012 11:45:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "tree.h"

GLfloat FractalTree::angleVariation  = 50;
GLfloat FractalTree::lengthFactor    = 0.7;
GLfloat FractalTree::thicknessFactor = 0.5;
GLfloat FractalTree::minTrunkLength  = 0.2;
GLint   FractalTree::subtreesNum     = 4;

FractalTree::FractalTree(
    GLfloat angleV,
    GLfloat lengthF,  
    GLfloat thicknessF,
    GLfloat minTrunkL,
    GLint   subtreesN) {

    angleVariation  = angleV;
    lengthFactor    = lengthF;
    thicknessFactor = thicknessF;
    minTrunkLength  = minTrunkL;
    subtreesNum     = subtreesN;
}
 

void FractalTree::generate(
    GLfloat length, 
    GLfloat thickness, 
    GLfloat y,
    GLfloat tx,
    GLfloat ty,
    GLfloat tz) {

    trunkLength = length;
    trunkThickness = thickness;
    thetaX = tx;
    thetaY = ty;
    thetaZ = tz;
    posY   = y;
    GLfloat range  = angleVariation;

    // If the trunkLength is still longer than the minTrunkLength, 
    // then keep drawing the tree recursively.
    if (trunkLength > minTrunkLength) {

        // Generate the subtrees.
        subtrees = new FractalTree*[subtreesNum];

        for (GLint i = 0; i < subtreesNum; ++i) {
            subtrees[i] = new FractalTree(
                angleVariation,
                lengthFactor, 
                thicknessFactor,
                minTrunkLength, 
                subtreesNum    
            );
            subtrees[i]->generate(
                trunkLength * lengthFactor,
                trunkThickness * thicknessFactor,
                trunkLength,
                RAND_RANGE(-range, range),
                RAND_RANGE(-range, range),
                RAND_RANGE(-range, range)
            );
        }
    }
    else {
        subtrees = NULL;
    }

}

void FractalTree::render() {

    glTranslatef(0, posY, 0);
    glRotatef(thetaX, 1.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);
    glRotatef(thetaZ, 0.0, 0.0, 1.0);

    glPushMatrix();

    glTranslatef(0, trunkLength/2.0, 0);
    glScalef(trunkThickness, trunkLength, trunkThickness);

    if (!subtrees)
        glColor3ub(0, 255, 0);
    else
        glColor3ub(144, 48, 0);

    glutSolidCube(1.0);

    glPopMatrix();

    if (subtrees) {
        for (GLint i = 0; i < subtreesNum; ++i) {
            glPushMatrix();
            subtrees[i]->render();
            glPopMatrix();
        }
    }

}
