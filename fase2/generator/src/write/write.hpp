#ifndef READ_H
#define READ_H

#include <iostream>
#include <fstream>
#include <vector>
#include "../classes/point.hpp"
#include "../classes/index.hpp"


using namespace std;

void create3d(string filename,vector<Point> &points,vector<Index> &index);


#endif