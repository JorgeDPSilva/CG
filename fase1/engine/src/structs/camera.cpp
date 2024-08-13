#include "camera.hpp"

Camera::Camera() {}

Camera::Camera(float position_x, float position_y, float position_z,float look_at_x, float look_at_y , float look_at_z, float up_x, float up_y, float up_z, float projection_x, float projection_y, float projection_z){
  vector<float> position = {position_x,position_y,position_z};
  this->position = position;
  
  vector<float> look_at = {look_at_x,look_at_y,look_at_z};
  this->look_at = look_at;
  
  vector<float> up = {up_x,up_y,up_z};
  this->up = up;
  
  vector<float> projection = {projection_x,projection_y,projection_z};
  this->projection = projection;
}

vector<float> Camera::get_position() {
  return this->position;
}

vector<float> Camera::get_look_at(){
  return this->look_at;
}

vector<float> Camera::get_up(){
  return this->up;
}

vector<float> Camera::get_projection(){
  return this->projection;
}

void Camera::set_position(float x, float y, float z){
  vector<float> position = {x,y,z};
  this->position = position;
}

void Camera::set_look_at(float x , float y, float z){
  vector<float> look_at = {x,y,z};
  this->look_at = look_at;
}

void Camera::set_up(float x, float y, float z){
  vector<float> up = {x,y,z};
  this->up = up;
}

void Camera::set_projection(float x, float y, float z){
  vector<float> projection = {x,y,z};
  this->projection = projection;
}

void Camera::parse_camera(XMLElement *camera_element) {
  for (XMLElement *camera_child = camera_element->FirstChildElement();camera_child; camera_child = camera_child->NextSiblingElement()) {
        
        string tag_name = camera_child->Name();
        float x = camera_child->FloatAttribute("x");
        float y = camera_child->FloatAttribute("y");
        float z = camera_child->FloatAttribute("z");


        if (tag_name == "position") {
            set_position(x, y, z);
        } else if (tag_name == "lookAt") {
            set_look_at(x, y, z);
        } else if (tag_name == "up") {
            set_up(x, y, z);
        } else if (tag_name == "projection") {
            float fov = camera_child->FloatAttribute("fov");
            float near = camera_child->FloatAttribute("near");
            float far = camera_child->FloatAttribute("far");
            set_projection(fov, near, far);
        }
    }
}

