#ifndef CATMULLROM_H
#define CATMULLROM_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

using namespace std;

void drawCatmullRomCurve(float t, vector<vector<float>> translation_points,bool align);

#endif