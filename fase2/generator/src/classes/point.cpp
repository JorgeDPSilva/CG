#include "point.hpp"


Point::Point() {};
Point::Point(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

float Point::getX(){
    return this->x;
}

float Point::getY(){
    return this->y;
}

float Point::getZ(){
    return this->z;
}

void Point::set_x(float x){
    this->x = x;
}

void Point::set_y(float y){
    this->y = y;
}

void Point::set_z(float z){
    this->z = z;
}


string Point::point_to_string() {
  return to_string(this->getX()) + " " + to_string(this->getY()) + " " +
         to_string(this->getZ());
}



