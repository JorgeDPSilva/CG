#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <math.h>
#include <vector>
#include "../../write/write.hpp"
#include "../../classes/point.hpp"
#include "../../classes/index.hpp"

using namespace std;

void sphere(float radius, int slices, int stacks, string filename);
void get_sphere_points(float radius, int stacks, int slices,vector<Point> &points);
void get_sphere_indexs(int slices, int stacks, int nPoints,vector<Index> &indexs);

#endif