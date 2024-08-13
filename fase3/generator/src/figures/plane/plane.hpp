#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <vector>
#include "../../write/write.hpp"
#include "../../classes/point.hpp"
#include "../../classes/index.hpp"

using namespace std;


void plane(float length, int divisions, string filename);
void get_plane_points(float length, int divisions,vector<Point> &points);
void get_plane_indexs(float length, int divisions,vector<Index> &index);

#endif