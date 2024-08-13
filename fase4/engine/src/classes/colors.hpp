#ifndef COLORS_H
#define COLORS_H

#include "../../lib/tinyxml2.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace tinyxml2;

class Colors {
private:
  vector<float> diffuse = {200, 200, 200};
  vector<float> ambient = {50, 50, 50};
  vector<float> specular = {0, 0, 0};
  vector<float> emissive = {0, 0, 0};
  float shininess = 0;

public:
  Colors();
  Colors(float diffuse_r, float diffuse_g, float diffuse_b, float ambient_r,
         float ambient_g, float ambient_b, float specular_r, float specular_g,
         float specular_b, float emissive_r, float emissive_g, float emissive_b,
         float value);
    vector<float> get_diffuse();
    vector<float> get_ambient();
    vector<float> get_specular();
    vector<float> get_emissive();
    float get_shininess();
  void set_diffuse(float r, float g, float b);
  void set_ambient(float r, float g, float b);
  void set_specular(float r, float g, float b);
  void set_emissive(float r, float g, float b);
  void set_value(float value);
  void parse_colors(XMLElement *colors_element);
};
#endif