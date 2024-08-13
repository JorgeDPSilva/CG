#include "cone.hpp"

void cone(float radius, float height, int slices, int stacks, string filename){
	vector<Point> points;
	vector<Index> index;
	get_cone_points(radius,height,slices,stacks,points);
	get_cone_indexs(slices,stacks,points.size()-1,index);
	create3d(filename,points,index);
}


void get_cone_points(float radius, float height, int slices, int stacks,
                     vector<Point> &points) {
  
  //dividir altura pelos stacks e calcula-se cada altura
  float heightRatio = height / (float)stacks;
  //dividing total circumference for number of slices we obtain the angles between each slice
  float sliceAng = 2*M_PI / (float)slices;

  //top of cone
  points.push_back(Point(0, height, 0));
  
  //run stacks começa a 1 para evitar que comece no ponto superior
  for (int i = 1; i <= stacks; i++) {
    //heigh of stacks
	float stack_height = height - (i * heightRatio); 
    //radius of stacks
	float stack_radius = i * (radius / stacks);
    //cicle for slices
	for (int j = 0; j < slices; j++) {
      float alpha = (M_PI/2) - (j * sliceAng);

      float px = stack_radius * cos(alpha);
      float py = stack_height;
      float pz = stack_radius * sin(alpha);

      points.push_back(Point(px, py, pz));
    }
  }
// ponto central da base 
  points.push_back(Point(0, 0, 0));
}

void get_cone_indexs(int slices, int stacks, int nPoints,vector<Index> &index) {
  
  //top of cone
  for (int i = 1; i <= slices; i++) {
    int index3 = (i % slices) + 1;

	index.push_back(Index(0, i, index3));
  }


  //middle
  for (int i = 1; i < nPoints - slices; i += slices) {
    for (int j = 0; j < slices; j++) {
      int t1_i1 = i + j;
      int t1_i2 = t1_i1 + slices;
      int t1_i3 = ((j + 1) % slices) + slices + i;
      index.push_back(Index(t1_i1, t1_i2, t1_i3));

      int t2_i3 = ((j + 1) % slices) + i;
      index.push_back(Index(t1_i1, t1_i3, t2_i3));
    }
  }

 //  bottom
  for (int i = 1; i <= slices; i++) {
    int index2 = nPoints - i;
    int index3 = nPoints - (i % slices) - 1;

    index.push_back(Index(nPoints, index2, index3));
  }
}



