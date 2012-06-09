/*
 * =====================================================================================
 *
 *       Filename:  sky.h
 *
 *    Description:  sky.h
 *
 *        Version:  1.0
 *        Created:  06/05/2012 02:23:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SKY_H
#define SKY_H

#include "const.h"

class Sky {

    public:
        Sky() {};
        ~Sky() {};

        void render(GLint width, GLuint texture);

};

#endif
