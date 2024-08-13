#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <vector>
#include <string>
#include <iostream>
#include "../../lib/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Transformation {
private:
string transformation; // like enum
vector<float> translate;
vector<float> rotate_angle;
vector<float> rotate_time;
vector<float> scale;
vector<vector <float>> translation_Points;
float translation_time;
bool translation_align;


public:
Transformation();
Transformation(float translate_x, float translate_y, float translate_z, float rotate_angle, float rotate_x, float rotate_y, float rotate_z, float scale_x, float scale_y, float scale_z);
vector<float> get_translate();
vector<float> get_rotate_angle();
vector<float> get_rotate_time();
vector<float> get_scale();
string get_transformation();
vector<vector<float>> get_translationPoints();
float get_translation_time();
bool get_translation_align();
void set_translate(float x, float y, float z);
void set_rotate(float angle, float x, float y, float z);
void set_scale(float x, float y, float z);
void set_rotatetime(float time, float x, float y, float z);
void parse_transformation(XMLElement *transformation_element);
};
#endif