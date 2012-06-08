/*
 * =====================================================================================
 *
 *       Filename:  smoke.h
 *
 *    Description:  Declaration of smoke. `dt` is default to be 1 in this implementation.
 *
 *        Version:  1.0
 *        Created:  06/08/2012 08:14:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SMOKE_H
#define SMOKE_H

#include "const.h"
#include "terrain.h"

#define IX(i, j)    ( i*(N+2)+j )
#define SWAP(x0, x) { GLfloat *tmp = x0; x0 = x; x = tmp; }

class Smoke {

    public:
        GLint N;
        GLfloat diff;
        GLfloat visc;

        GLfloat *d;
        GLfloat *d_prev;
        GLfloat *u;
        GLfloat *u_prev;
        GLfloat *v;
        GLfloat *v_prev;

    public:
        Smoke(GLint n, GLfloat d, GLfloat v);
        ~Smoke();

        void evolve();
        void render(GLfloat s);

    private:
        void density_step();
        void velocity_step();
        void project(GLfloat *p, GLfloat *div);

        void add_source(GLfloat *d, GLfloat *s);
        void diffuse(GLint b, GLfloat *d, GLfloat *d_prev);
        void advert(GLint b, GLfloat *d, GLfloat *d_prev, GLfloat *u, GLfloat *v);
        void set_bound(GLint b, GLfloat *x);
        GLfloat get_max_density();

};

#endif
