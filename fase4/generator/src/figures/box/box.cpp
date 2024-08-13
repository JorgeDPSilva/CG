#include "box.hpp"

void box(float length, int divisions, string filename) {
  vector<Point> points;
  vector<Index> index;
  get_box_points(length, divisions, points);
  get_box_indexs(length, divisions, index);
  create3d(filename, points, index);
}

void get_box_points(float length, int divisions, vector<Point> &points) {
  float halfLength = length / 2.0;

  // Bottom face (y = -halfLength)
  for (int i = 0; i <= divisions; i++) {
    for (int j = 0; j <= divisions; j++) {
      float px = -halfLength + (j * (length / divisions));
      float pz = halfLength - (i * (length / divisions));
      points.push_back(Point(px, -halfLength, pz));
    }
  }

  // Top face (y = halfLength)
  for (int i = 0; i <= divisions; i++) {
    for (int j = 0; j <= divisions; j++) {
      float px = -halfLength + (j * (length / divisions));
      float pz = halfLength - (i * (length / divisions));
      points.push_back(Point(px, halfLength, pz));
    }
  }

  // Front face (z = halfLength)
  for (int i = 0; i <= divisions; i++) {
    for (int j = 0; j <= divisions; j++) {
      float px = -halfLength + (j * (length / divisions));
      float py = -halfLength + (i * (length / divisions));
      points.push_back(Point(px, py, halfLength));
    }
  }

  // Back face (z = -halfLength)
  for (int i = 0; i <= divisions; i++) {
    for (int j = 0; j <= divisions; j++) {
      float px = -halfLength + (j * (length / divisions));
      float py = -halfLength + (i * (length / divisions));
      points.push_back(Point(px, py, -halfLength));
    }
  }

  // Left face (x = -halfLength)
  for (int i = 0; i <= divisions; i++) {
    for (int j = 0; j <= divisions; j++) {
      float py = -halfLength + (i * (length / divisions));
      float pz = halfLength - (j * (length / divisions));
      points.push_back(Point(-halfLength, py, pz));
    }
  }

  // Right face (x = halfLength)
  for (int i = 0; i <= divisions; i++) {
    for (int j = 0; j <= divisions; j++) {
      float py = -halfLength + (i * (length / divisions));
      float pz = halfLength - (j * (length / divisions));
      points.push_back(Point(halfLength, py, pz));
    }
  }
}

void get_box_indexs(float length, int divisions, vector<Index> &index) {
  int face_points = pow(divisions + 1, 2);

  for (int face = 0; face < 6; face++) {
    for (int i = 0; i < divisions * divisions; i += divisions + 1) {
      for (int j = 0; j < divisions; j++) {
        int topleft = j + i + (face * face_points);
        int topright = j + i + divisions + 1 + (face * face_points);
        int bottomright = j + i + divisions + 2 + (face * face_points);
        int bottomleft = j + i + 1 + (face * face_points);

        if (face == 0) { // bottom face
          index.push_back(Index(bottomleft, topleft, topright));
          index.push_back(Index(bottomleft, topright, bottomright));
        } else if (face == 1) { // top face
          index.push_back(Index(topleft, bottomleft, bottomright));
          index.push_back(Index(topleft, bottomright, topright));
        } else if (face == 2) { // front face
          index.push_back(Index(topleft, bottomleft, bottomright));
          index.push_back(Index(topleft, bottomright, topright));
        } else if (face == 3) { // back face
          index.push_back(Index(bottomleft, topleft, bottomright));
          index.push_back(Index(topleft, topright, bottomright));
        } else if (face == 4) { // left face
          index.push_back(Index(topright, bottomright, bottomleft));
          index.push_back(Index(topright, bottomleft, topleft));
        } else { // right face
          index.push_back(Index(topleft, bottomleft, bottomright));
          index.push_back(Index(topleft, bottomright, topright));
        }
      }
    }
  }
}
