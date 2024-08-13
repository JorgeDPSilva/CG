#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../../lib/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Model{
    
    private:
    string file;
    vector<vector <float>> points;
    vector<vector <int>> index;

    public:
    Model();
    Model(string newFile);


    string get_file();
    vector<vector <float>> get_points();
    vector<vector <int>> get_index();
    void set_file(string newFile);
    void set_points(vector<vector<float>> points);
    void set_index(vector<vector <int>> index);
    void parse_model(XMLElement *model_elements);
    void readPointsFromFile();
    

};
#endif