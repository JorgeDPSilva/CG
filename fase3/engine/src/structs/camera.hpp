#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <string>
#include "../../lib/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Camera {

private:
vector<float> position;
vector<float> look_at;
vector<float> up;
vector<float> projection;


public:
Camera();
Camera(float position_x, float position_y, float position_z,float look_at_x, float look_at_y , float look_at_z, float up_x, float up_y, float up_z, float projection_x, float projection_y, float projection_z);

vector<float> get_position();
vector<float> get_look_at();
vector<float> get_up();
vector<float> get_projection();

void set_position(float x, float y, float z);
void set_look_at(float x , float y, float z);
void set_up(float x, float y, float z);
void set_projection(float x, float y , float z);
void parse_camera(XMLElement *camera_element);
};



#endif