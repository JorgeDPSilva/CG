#ifndef LIGHTS_H
#define LIGHTS_H


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include "../../lib/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Lights {
private:
vector<float> directional;
vector<float> positional;
string type;
float cutoff;



public:
Lights();
vector<float> get_lights_directional();
vector<float> get_lights_positional();
vector<float> get_lights_spot();
string get_type();
float get_cutoff();
void enable_light(int index);
void setup_light(int index);
void set_lights_directional(float dirX, float dirY, float dirZ);
void set_lights_positional(float posX, float posY, float posZ);
void set_lights_spot(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float cutoff);
void parse_lights(XMLElement *lights_elements,int index);

};
#endif