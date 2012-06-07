#include "bmpReader.h"

GLbyte* bmpReader(const char *filename, GLint &width, GLint &height) {

    ifstream file(filename, ios::in | ios::binary);
    if (!file)
        return NULL;

    // Read width and height of the image(in pixel).
    const ifstream::off_type widthOffset = 18;
    file.seekg(widthOffset, ios::beg);

    char ch1, ch2, ch3, ch4;

    file.get(ch4).get(ch3).get(ch2).get(ch1);
    width = width | ((int)ch1 & 0xff);
    width = width << 8 | ((int)ch2 & 0xff);
    width = width << 8 | ((int)ch3 & 0xff);
    width = width << 8 | ((int)ch4 & 0xff);

    cout << width << endl;

    file.get(ch4).get(ch3).get(ch2).get(ch1);
    height = height | ((int)ch1 & 0xff);
    height = height << 8 | ((int)ch2 & 0xff);
    height = height << 8 | ((int)ch3 & 0xff);
    height = height << 8 | ((int)ch4 & 0xff);

    cout << height << endl;

    // Get number of bits per pixel.
    GLbyte* image = new GLbyte[width * height * 3];

    const ifstream::off_type bitsPerPixelOffset = 28;
    file.seekg(bitsPerPixelOffset, ios::beg);

    int bitsPerPixel = 0;
    file.get(ch2).get(ch1);
    bitsPerPixel = bitsPerPixel | ((int)ch1 & 0xff);
    bitsPerPixel = bitsPerPixel << 8 | ((int)ch2 & 0xff);

    // Get image information.
    const ifstream::off_type skipBytes = 54;
    file.seekg(skipBytes, ios::beg);

    int makeupBytes = 4 - width * 3 % 4;
    makeupBytes = makeupBytes == 4 ? 0 : makeupBytes;
    char temp;

    for (GLint y = 0; y < height; ++y) {
        for (GLint x = 0; x < width; ++x) {
            char r, b, g;
            file.get(b).get(g).get(r);

            image[3*y*width + 3*x] = b;
            image[3*y*width + 3*x + 1] = g;
            image[3*y*width + 3*x + 2] = r;
        }

        for (GLint i = 0; i < makeupBytes; ++i)
            file.get(temp);

    }

    file.close();
    return image;

}
