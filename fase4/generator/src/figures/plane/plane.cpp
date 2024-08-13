#include "plane.hpp"

void plane(float length, int divisions, string filename){
	vector<Point> points;
	vector<Index> index;
	get_plane_points(length, divisions,points);
  get_plane_indexs(length,divisions,index);
  create3d(filename,points,index);

}

void get_plane_points(float length, int divisions,vector<Point> &points) {	
  for (int i = 0; i <= divisions; i++) {
    for (int j = 0; j <= divisions; j++) {
      float px = -(length / 2) + (j * (length / divisions));
      float pz = -(length / 2) + (i * (length / divisions));

      points.push_back(Point(px,0,pz));
    }
  }
}

void get_plane_indexs(float length, int divisions,vector<Index> &index){
// i += divisions + 1 = numbers of points on the same line
for (int i = 0; i < divisions * divisions; i += divisions + 1) {
        //Coluns
		for (int j = 0; j < divisions  ; j++) {
            int upleft = j + i;
            int bottomleft = j + i + divisions + 1;
            int bottomright = j + i + divisions + 2;
			      int upright = j + i + 1;

      // first triangle
			index.push_back(Index(upleft,bottomleft ,bottomright));
      //second
      index.push_back(Index(upleft,bottomright ,upright));
        }
      
    }
}
