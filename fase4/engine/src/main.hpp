#ifndef ENGINE_H
#define ENGINE_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "../lib/tinyxml2.h"
#include "classes/camera.hpp"
#include "classes/group.hpp"
#include "classes/model.hpp"
#include "classes/window.hpp"
#include "classes/catmullrom.hpp"
#include "classes/colors.hpp"
#include "classes/transformation.hpp"
#include "classes/lights.hpp"

using namespace tinyxml2;
using namespace std;


#endif