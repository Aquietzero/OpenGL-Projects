/*
 * =====================================================================================
 *
 *       Filename:  sky.cpp
 *
 *    Description:  sky.cpp
 *
 *        Version:  1.0
 *        Created:  06/05/2012 02:32:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "sky.h"

void Sky::render(GLint width, GLuint texture) {

    glFrontFace(GL_CW);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glutSolidSphere(width, 50, 50);

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

    glFrontFace(GL_CCW);

}
