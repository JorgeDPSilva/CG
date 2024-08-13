#include "write.hpp"


void create3d(string filename,vector<Point> &points,vector<Index> &index){
    ofstream file;
    
    file.open(filename);
   //write number of points
     file << to_string(points.size()) + "\n";
    for (Point point : points) {
    file << point.point_to_string() + "\n";
  }


    file << to_string(index.size()) + "\n";
  for (Index index : index) {
    file << index.index_to_string() + "\n";
  }

    file.close();

}