#include "const.h"
#include "lib/bmpReader.h"

void setupRC() {

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_COLOR_SUM);

    setupLightAndMaterial();
    setupTexture();

}

void setupLightAndMaterial() {

    GLfloat ambientLight[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat diffuseLight[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat specularLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightSource[]  = {14.0, 10.0, 14.0, 1.0};

    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);


    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightSource);

    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

}

void setupTexture() {

    GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glGenTextures(TEXTURE_COUNT, textures);
    for (GLint i = 0; i < TEXTURE_COUNT; ++i) {

        iWidth = 0;
        iHeight = 0;


        glBindTexture(GL_TEXTURE_2D, textures[i]);

        // Load texture
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        pBytes = bmpReader(textures_src[i], iWidth, iHeight);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, iWidth, iHeight, 
                0, GL_BGR, GL_UNSIGNED_BYTE, pBytes);

        GLfloat fLargest;

        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
        
        free(pBytes);

    }

}
