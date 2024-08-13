#include "sphere.hpp"

void sphere(float radius, int slices, int stacks, string filename){
	vector<Point> points;
	vector<Index> index;
	get_sphere_points(radius,stacks,slices,points);
	get_sphere_indexs(slices,stacks,points.size()-1,index);
	create3d(filename,points,index);
}

void get_sphere_points(float radius, int stacks, int slices,vector<Point> &points) {
  //calculates the angle between the top and bottom points of the sphere(-π/2 a π/2)
  float stack_angle = ((M_PI) / (float)stacks);
  float slice_angle = (2 * M_PI) / (float)slices;

  points.push_back(Point(0, -radius, 0));

  for (int i = 1; i < stacks; i++) {
    float beta = (i * stack_angle) - (M_PI/2);
    for (int j = 0; j < slices; j++) {
      float alpha = j * slice_angle;

      float px = radius * cos(beta) * sin(alpha);
      float py =  radius * sin(beta);
      float pz = radius * cos(beta) * cos(alpha);

      points.push_back(Point(px, py, pz));
    }
  }

  points.push_back(Point(0, radius, 0));
}


void get_sphere_indexs(int slices, int stacks, int nPoints,vector<Index> &indexs) {
  
  for (int i = 1; i <= slices; i++) {
    int index2 = (i % slices) + 1;
    indexs.push_back(Index(0, index2, i));
  }

  for (int i = 1; i < nPoints - slices; i += slices) {
    for (int j = 0; j < slices; j++) {
      int t1_i1 = i + j;
      int t1_i2 = ((j + 1) % slices) + i + slices;
      int t1_i3 = t1_i1 + slices;
      indexs.push_back(Index(t1_i1, t1_i2, t1_i3));

      int t2_i2 = ((j + 1) % slices) + i;
      indexs.push_back(Index(t1_i1, t2_i2, t1_i2));
    }
  }

  for (int i = 1; i <= slices; i++) {
    int index1 = nPoints;
    int index2 = index1 - (i % slices) - 1;
    int index3 = index1 - i;
    indexs.push_back(Index(index1, index2, index3));
  }
}