/*
 * =====================================================================================
 *
 *       Filename:  theme.h
 *
 *    Description:  Theme.
 *
 *        Version:  1.0
 *        Created:  06/10/2012 10:23:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#ifndef THEME_BASIC_H
#define THEME_BASIC_H

class Theme {

    public:

        GLuint  sky;
        GLuint  terrain;
        GLuint  water;

        GLfloat sky_color[4];
        GLfloat terrain_color[4];
        GLfloat water_color_start[4];
        GLfloat water_color_stop[4];

        GLfloat fog_color[4];

        Theme(GLuint sky_texture, GLuint terrain_texture, GLuint water_texture) {

            sky     = sky_texture;
            terrain = terrain_texture;
            water   = water_texture;

        }

};

class MorningTheme : public Theme {

    public:

        MorningTheme(GLuint sky_texture, GLuint terrain_texture, GLuint water_texture)
            : Theme(sky_texture, terrain_texture, water_texture) {

            sky_color[0] = 0.0;
            sky_color[1] = 0.0;
            sky_color[2] = 0.0;
            sky_color[3] = 0.0;

            terrain_color[0] = 0.2;
            terrain_color[1] = 0.2;
            terrain_color[2] = 0.45;
            terrain_color[3] = 0.0;

            water_color_start[0] = 0.3;
            water_color_start[1] = 0.4;
            water_color_start[2] = 0.65;
            water_color_start[3] = 0.8;

            water_color_stop[0] = 0.3;
            water_color_stop[1] = 0.4;
            water_color_stop[2] = 0.65;
            water_color_stop[3] = 0.8;

            fog_color[0] = 0.7;
            fog_color[1] = 0.75;
            fog_color[2] = 0.8;
            fog_color[3] = 0.1;

        }

};

class SunsetTheme : public Theme {

    public:

        SunsetTheme(GLuint sky_texture, GLuint terrain_texture, GLuint water_texture)
            : Theme(sky_texture, terrain_texture, water_texture) {

            sky_color[0] = 0.0;
            sky_color[1] = 0.0;
            sky_color[2] = 0.0;
            sky_color[3] = 1.0;

            terrain_color[0] = 0.2;
            terrain_color[1] = 0.2;
            terrain_color[2] = 0.25;
            terrain_color[3] = 0.3;

            water_color_start[0] = 0.65;
            water_color_start[1] = 0.1;
            water_color_start[2] = 0.1;
            water_color_start[3] = 0.9;

            water_color_stop[0] = 0.05;
            water_color_stop[1] = 0.0;
            water_color_stop[2] = 0.0;
            water_color_stop[3] = 0.8;

            fog_color[0] = 0.55;
            fog_color[1] = 0.4;
            fog_color[2] = 0.0;
            fog_color[3] = 0.05;

        }

};

#endif
