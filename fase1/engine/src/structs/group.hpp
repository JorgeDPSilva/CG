#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include "model.hpp"
#include "../../lib/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Group{

private:
    vector<Model> models;

public:
Group();
Group(vector<Model> models);

void parse_group(XMLElement* group_element);
vector<Model> get_models();
void set_models(vector<Model> models);


};


#endif