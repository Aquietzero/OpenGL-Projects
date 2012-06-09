#include "terrain.h"

/* The size of the terrain must be the power of 2. if the size is
 * not the power of 2, then the size will be automatically shrink
 * to an integer which is the closest one to the origin number but
 * at the same time, the new size is the power of 2.
 */
Terrain::Terrain(const int s, const float max_h, const float r) 
    :max_height(max_h), roughness(r) {

    size = isPowerOf2(s) ? s : closestPowerOf2lt(s);

    // Allocate the terrain.
    terrain = new float*[size+1];
    terrainPlaneNormals = new float**[size+1];
    for (int i = 0; i <= size; ++i) {
        terrain[i] = new float[size+1];
        terrainPlaneNormals[i] = new float*[size+1];

        for (int j = 0; j <= size; ++j) {
            terrain[i][j] = 0.0;
            terrainPlaneNormals[i][j] = new float[3];
            terrainPlaneNormals[i][j][0] = 0.0;
            terrainPlaneNormals[i][j][1] = 1.0;
            terrainPlaneNormals[i][j][2] = 0.0;
        }
    }

}

Terrain::~Terrain() {

    for (int i = 0; i < size; ++i)
        delete [] terrain[i];
    delete [] terrain;

}

void Terrain::generate() {

    int step = size / 2;
    float r = 1;

    while (step > 1) {
        for (int i = 0; i < size; i += step)
            for (int j = 0; j < size; j += step) 
                diamond(i, j, step, r);

        for (int i = 0; i < size; i += step)
            for (int j = 0; j < size; j += step) 
                square(i, j, step, r);

        step /= 2;
        r *= pow(2, -roughness);
    }

    smooth();

}

/* The coordinates are shown as below:
 *
 * (x, y)
 *    \
 *    a --- b --- c
 *    |  \  |  /  |
 *    d --- e --- f
 *    |  /  |  \  |
 *    g --- h --- i
 *
 * where:
 *
 *  a -> terrain[x][y]
 *  c -> terrain[x+step][y]
 *  g -> terrain[x][y+step]
 *  i -> terrain[x+step][y+step]
 *
 * The purpose of the DIAMOND method is to calculate the
 * height of e through a, c, g, i.
 */
void Terrain::diamond(int x, int y, int step, float r) {

    float baseHeight = 
        avg(terrain[x][y], 
            terrain[x+step][y],
            terrain[x][y+step], 
            terrain[x+step][y+step]);

    terrain[x+step/2][y+step/2] = 
        baseHeight + r*getRandom(-max_height, max_height);

}

/* The coordinates are shown as below:
 *
 * (x, y)
 *    \
 *    a --- b --- c
 *    |  \  |  /  |
 *    d --- e --- f
 *    |  /  |  \  |
 *    g --- h --- i
 *
 * where:
 *
 *  b -> terrain[x+half][y]
 *  d -> terrain[x][y+half]
 *  f -> terrain[x+step][y+half]
 *  h -> terrain[x+half][y+step]
 *
 * The purpose of the DIAMOND method is to calculate the
 * height of:
 *
 *  b -> through b_up, c, e, a
 *  d -> through a, e, g, d_left
 *  f -> through c, f_right, i, e
 *  h -> through e, i, h_down, g
 */

void Terrain::square(int x, int y, int step, float r) {

    int half = step / 2;

    float a = terrain[x][y];
    float c = terrain[x+step][y];
    float e = terrain[x+half][y+half];
    float g = terrain[x][y+step];
    float i = terrain[x+step][y+step];

    // Check the validity of the neighbours of b, d, f, h.
    float b_up, d_left, f_right, h_down;
    b_up    = y - half < 0 ? terrain[x+half][size-half] : terrain[x+half][y-half];
    d_left  = x - half < 0 ? terrain[size-half][y+half] : terrain[x-half][y+half];
    f_right = x + 3*half > size ? terrain[half][y+half] : terrain[x+3*half][y+half];
    h_down  = y + 3*half > size ? terrain[x+half][half] : terrain[x+half][y+3*half];

    terrain[x+half][y] = avg(b_up, c, e, a)   + r*getRandom(-max_height, max_height);
    terrain[x][y+half] = avg(a, e, g, d_left) + r*getRandom(-max_height, max_height);
    terrain[x+step][y+half] = avg(c, f_right, i, e) + r*getRandom(-max_height, max_height);
    terrain[x+half][y+step] = avg(e, i, h_down, g)  + r*getRandom(-max_height, max_height);

}

void Terrain::render(int s, float c[], GLuint texture, RENDER_TYPE t) {

    switch(t) {
        case SOLID:
            renderSolidTerrain(s, c, texture);
            break;
        case WIRE:
            renderWireTerrain(s, c);
            break;
        default:
            renderWireTerrain(s, c);
            break;
    }

}

void Terrain::renderWireTerrain(int s, float c[]) {

    GLfloat step = (GLfloat)2*s / size;
    GLfloat x = -(GLfloat)s;
    GLfloat z = -(GLfloat)s;

    //glColor3fv(c);
    glColor3f(0.0, 0.0, 0.0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            glVertex3f(x, terrain[i][j], z);
            glVertex3f(x, terrain[i][j+1], z+step);
            glVertex3f(x+step, terrain[i+1][j+1], z+step);
            glVertex3f(x+step, terrain[i+1][j], z);

            z += step;
        }
        x += step;
        z = -(GLfloat)s;
    }
    glEnd();
}

void Terrain::renderSolidTerrain(int s, float c[], GLuint texture) {

    GLfloat step = (GLfloat)2*s / size;
    GLfloat x = -(GLfloat)s;
    GLfloat z = -(GLfloat)s;
    //GLfloat *nv;

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4f(c[0], c[1], c[2], c[3]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            glNormal3fv(terrainPlaneNormals[i][j]);
            
            glTexCoord2f((float)i/size, (float)j/size);
            glVertex3f(x, terrain[i][j], z);

            glTexCoord2f((float)i/size, (float)(j+1)/size);
            glVertex3f(x, terrain[i][j+1], z+step);

            glTexCoord2f((float)(i+1)/size, (float)(j+1)/size);
            glVertex3f(x+step, terrain[i+1][j+1], z+step);

            glTexCoord2f((float)(i+1)/size, (float)j/size);
            glVertex3f(x+step, terrain[i+1][j], z);


            z += step;
        }
        x += step;
        z = -(GLfloat)s;
    }
    glEnd();

}

Vector2D<GLint>* Terrain::perfectSpots(int num) {

    // Limit the largest number of perfect spots, or it
    // won't be perfect, it just ordinary.
    num = num > 10 ? 10 : num;

    Vector2D<GLint>* spots = new Vector2D<GLint>[num];
    Vector2D<GLint> max, offset;

    for (int i = 5; i < size - 5; ++i)
        for (int j = 5; j < size - 5; ++j) {
            if (terrain[i][j] > terrain[max.x][max.y]) {
                max.x = i;
                max.y = j;
            }
        }

    spots[0] = max;
    for (int i = 1; i < num; ++i) {
        offset = Vector2D<GLint>(getRandom(-5, 5), getRandom(-5, 5));
        spots[i] = max + offset;
    }

    return spots;

}

void Terrain::smooth() {

    GLfloat **tempTerrain = new GLfloat*[size];
    for (int i = 0; i < size; ++i)
        tempTerrain[i] = new GLfloat[size];

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            tempTerrain[i][j] = terrain[i][j];

    GLfloat sum;
    for (int i = 1; i < size - 1; ++i) {
        for (int j = 1; j < size - 1; ++j) {
            sum = 0;
            for (int m = -1; m <= 1; ++m)
                for (int n = -1; n <= 1; ++n)
                    sum += tempTerrain[i+n][j+m];
            terrain[i][j] = sum / 9.0;
        }
    }

}

void Terrain::setPlaneNormals(int s) {

    GLfloat step = (GLfloat)2*s / size;
    for (int i = 0; i < size; ++i) 
        for (int j = 0; j < size; ++j) 
            getNormalVector2fv(0, terrain[i+1][j]-terrain[i][j], step,
                               step, terrain[i+1][j+1]-terrain[i+1][j], 0, 
                               terrainPlaneNormals[i][j]);

}

