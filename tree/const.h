/*
 * =====================================================================================
 *
 *       Filename:  const.h
 *
 *    Description:  const.h defines some const in the demo and some useful little functions.
 *
 *        Version:  1.0
 *        Created:  05/24/2012 10:03:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#pragma once

#include <stdlib.h>
#include <math.h>

#include <GL/glu.h>
#include <GL/glut.h>

#define PI 3.1415926

#define MAX2(x, y) ( x > y ? x : y ) 
#define MIN2(x, y) ( x > y ? y : x )

#define RADIAN(x) ( x * PI / 180 )
#define DEGREE(x) ( x * 180 / PI )

#define RAND()           ( rand()/(float)RAND_MAX )
#define RAND_RANGE(x, y) ( x + RAND() * (y - x) )
