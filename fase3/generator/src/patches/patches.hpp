
#ifndef PATCHES_H
#define PATCHES_H


#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "../write/write.hpp"
#include "../classes/point.hpp"
#include "../classes/index.hpp"

using namespace std;

void readPatchFile(string filename, int tesselation, string final_filename);


#endif
