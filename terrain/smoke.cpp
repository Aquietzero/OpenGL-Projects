/*
 * =====================================================================================
 *
 *       Filename:  smoke.cpp
 *
 *    Description:  Definition of smoke. `dt` is default to be 1 in this implementation.
 *
 *        Version:  1.0
 *        Created:  06/08/2012 08:29:40 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include "smoke.h"

Smoke::Smoke(GLint n, GLfloat diffuse, GLfloat viscosity) {

    N = n;
    diff = diffuse;
    visc = viscosity;
    GLint size = (N + 2) * (N + 2);

    d      = new GLfloat[size];
    u      = new GLfloat[size];
    v      = new GLfloat[size];
    d_prev = new GLfloat[size];
    u_prev = new GLfloat[size];
    v_prev = new GLfloat[size];

    for (int i = 0; i < size; ++i) {
        d[i]      = 0;
        u[i]      = 0;
        v[i]      = 0;
        d_prev[i] = 0;
        u_prev[i] = 0;
        v_prev[i] = 0;
    }

    Terrain *t = new Terrain(N, 3.0, 1.0);
    t->generate();
    for (int i = 1; i < N; ++i)
        for (int j = 1; j < N; ++j) {
            // d[IX(i, j)] = t->terrain[i][j];
            // u[IX(i, j)] = t->terrain[i][j];
            // v[IX(i, j)] = t->terrain[i][j];
            d_prev[IX(i, j)] = t->terrain[i][j];
            u_prev[IX(i, j)] = t->terrain[i][j];
            v_prev[IX(i, j)] = t->terrain[i][j];
        }

}

Smoke::~Smoke() {

    delete[] d;
    delete[] u;
    delete[] v;
    delete[] d_prev;
    delete[] u_prev;
    delete[] v_prev;

}

void Smoke::add_source(GLfloat* d, GLfloat *s) {

    GLint size = (N + 2) * (N + 2);

    for (int i = 0; i < size; ++i)
        d[i] += s[i];

}

void Smoke::diffuse(GLint b, GLfloat *d, GLfloat *d_prev) {

    GLfloat factor = diff * N * N;
  
    for (int k = 0; k < 20; ++k) {
        for (int i = 1; i < N; ++i) {
            for (int j = 1; j < N; ++j) {
                d[IX(i,j)] = (d_prev[IX(i, j)] + factor*(
                        d[IX(i-1,j)] +
                        d[IX(i+1,j)] +
                        d[IX(i,j-1)] +
                        d[IX(i,j+1)]
                        )) / (1 + 4*factor);
            }
        }
        set_bound(b, d);
    }

}

void Smoke::advert(GLint b, GLfloat *d, GLfloat *d_prev, GLfloat *u, GLfloat *v) {

    GLint   i, j, i0, j0, i1, j1;
    GLfloat x, y, s0, t0, s1, t1, dt0;

    dt0 = N;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {

            x = i - dt0*u[IX(i,j)]; 
            y = j - dt0*v[IX(i,j)];
            
            if (x < 0.5) x=0.5; 
            if (x > N+0.5) x = N + 0.5; i0 = (int)x; i1 = i0 + 1;
            if (y < 0.5) y=0.5; 
            if (y > N+0.5) y = N + 0.5; j0 = (int)y; j1 = j0 + 1;
            
            s1 = x - i0; 
            s0 = 1 - s1; 
            t1 = y - j0; 
            t0 = 1 - t1;

            d[IX(i,j)] = 
                s0 * (t0 * d_prev[IX(i0,j0)] + t1 * d_prev[IX(i0,j1)]) +
                s1 * (t0 * d_prev[IX(i1,j0)] + t1 * d_prev[IX(i1,j1)]);

        }
    }
    set_bound(b, d);

}

void Smoke::density_step() {

    add_source(d, d_prev);
    SWAP(d_prev, d); diffuse(0, d, d_prev);
    SWAP(d_prev, d); advert(0, d, d_prev, u, v);

}

void Smoke::velocity_step() {

    add_source(u, u_prev);
    add_source(v, v_prev);

    SWAP(u, u_prev); diffuse(1, u, u_prev);
    SWAP(v, v_prev); diffuse(2, v, v_prev);

    project(u_prev, v_prev);
    SWAP(u, u_prev);
    SWAP(v, v_prev);

    advert(1, u, u_prev, u_prev, v_prev);
    advert(2, v, v_prev, u_prev, v_prev);
    project(u_prev, v_prev);

}

void Smoke::project(GLfloat *p, GLfloat *div) {

    GLint   i, j, k;
    GLfloat h;
    h = 1.0/N;

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            div[IX(i,j)] = -0.5 * h *
                (u[IX(i+1,j)] - 
                 u[IX(i-1,j)] +
                 v[IX(i,j+1)] -
                 v[IX(i,j-1)]);
            p[IX(i,j)] = 0;
        }
    }

    set_bound(0, div); 
    set_bound(0, p);
    for (k = 0; k < 20; ++k) {
        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= N; ++j) {
                p[IX(i,j)] = 
                    (div[IX(i,j)] +
                     p[IX(i-1,j)] +
                     p[IX(i+1,j)] +
                     p[IX(i,j-1)] +
                     p[IX(i,j+1)])/4;
            }
        }
        set_bound(0, p);
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            u[IX(i,j)] -= 0.5 * (p[IX(i+1,j)] - p[IX(i-1,j)])/h;
            v[IX(i,j)] -= 0.5 * (p[IX(i,j+1)] - p[IX(i,j-1)])/h;
        }
    }
    set_bound(1, u); 
    set_bound(2, v);

}

void Smoke::set_bound(GLint b, GLfloat *x) {

    for (int i = 1; i <= N; ++i) {
        x[IX(0,  i)] = b == 1 ? -x[IX(1,i)] : x[IX(1,i)];
        x[IX(N+1,i)] = b == 1 ? -x[IX(N,i)] : x[IX(N,i)];
        x[IX(i,  0)] = b == 2 ? -x[IX(i,1)] : x[IX(i,1)];
        x[IX(i,N+1)] = b == 2 ? -x[IX(i,N)] : x[IX(i,N)];
    }

    x[IX(0,   0)]  = 0.5 * (x[IX(1,  0)] + x[IX(0,  1)]);
    x[IX(0, N+1)]  = 0.5 * (x[IX(1,N+1)] + x[IX(0,  N)]);
    x[IX(N+1, 0)]  = 0.5 * (x[IX(N,  0)] + x[IX(N+1,1)]);
    x[IX(N+1,N+1)] = 0.5 * (x[IX(N,N+1)] + x[IX(N+1,N)]);

}

void Smoke::evolve() {

    velocity_step();
    density_step();

}

void Smoke::render(GLfloat s) {

    GLfloat step = (GLfloat)2*s / N;
    GLfloat x = -(GLfloat)s;
    GLfloat y = -(GLfloat)s;
    GLfloat max_density = get_max_density();
    GLfloat alpha;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBegin(GL_QUADS);
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) { 

            alpha = max_density == 0 ? 0 : d[IX(i, j)]/max_density;
            glColor4f(0.5, 0.5, 0.5, alpha);

            glVertex2f(x     , y);
            glVertex2f(x+step, y);
            glVertex2f(x+step, y+step);
            glVertex2f(x     , y+step);
            x += step;

        }
        y += step;
        x = -(GLfloat)s;
    }
    glEnd();
    glDisable(GL_BLEND);

}

GLfloat Smoke::get_max_density() {

    GLfloat max = 0;
    GLint   size = (N + 2) * (N + 2);

    for (int i = 0; i < size; ++i)
        if (d[i] > max)
            max = d[i];

    return max;

}
