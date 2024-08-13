#ifndef CONE_H
#define CONE_H

#include <iostream>
#include <math.h>
#include "../../write/write.hpp"
#include "../../classes/point.hpp"
#include "../../classes/index.hpp"

using namespace std;

void cone(float radius, float height, int slices, int stacks, string filename);
void get_cone_points(float radius, float height, int slices, int stacks,vector<Point> &points);
void get_cone_indexs(int slices, int stacks, int nPoints,vector<Index> &index);

#endif