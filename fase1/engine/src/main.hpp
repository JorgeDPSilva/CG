#ifndef ENGINE_H
#define ENGINE_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>
#include "../lib/tinyxml2.h"
#include "structs/camera.hpp"
#include "structs/group.hpp"
#include "structs/model.hpp"
#include "structs/window.hpp"

using namespace tinyxml2;
using namespace std;


#endif