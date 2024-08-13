#ifndef MODEL_H
#define MODEL_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../../lib/tinyxml2.h"
#include "colors.hpp"






using namespace std;
using namespace tinyxml2;

class Model{
    
    private:
    string file;
    GLuint indexBuffer;
    GLuint vertexBuffer;
    int numPoints;
    Colors colors;

    public:
    Model();
    Model(string newFile);


    string get_file();
    GLuint get_points();
    GLuint get_index();
    Colors get_colors();
    int get_numPoints();
    void set_file(string newFile);
    void set_points(GLuint points);
    void set_index(GLuint index);
    void parse_model(XMLElement *model_elements);
    void readPointsFromFile();
    

};
#endif

