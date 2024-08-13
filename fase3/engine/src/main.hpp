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
#include "structs/camera.hpp"
#include "structs/group.hpp"
#include "structs/model.hpp"
#include "structs/window.hpp"
#include "structs/catmullrom.hpp"

using namespace tinyxml2;
using namespace std;


#endif