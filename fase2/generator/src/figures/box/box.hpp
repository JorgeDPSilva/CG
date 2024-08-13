#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <vector>
#include <math.h>
#include "../../write/write.hpp"
#include "../../classes/point.hpp"
#include "../../classes/index.hpp"

using namespace std;

void box(float length, int divisions, string filename);
void get_box_points(float length, int divisions, vector<Point> &points);
void get_box_indexs(float length,int divisions, vector<Index> &indices);

#endif