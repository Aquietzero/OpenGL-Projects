#ifndef BMP_READER
#define BMP_READER

#include <iostream>
#include <fstream>
#include <GL/glut.h>

using namespace std;

GLbyte* bmpReader(const char *filename, GLint &width, GLint &height);

#endif
