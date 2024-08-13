#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <tuple>
using namespace std;


class Point {

private:
    float x;
    float y;
    float z;
    

public:   
    Point();
    Point(float x, float y, float z);
    
    float getX();
    float getY();
    float getZ();
    

    void set_x(float x);
    void set_y(float y);
    void set_z(float z);
    string point_to_string();
};


#endif