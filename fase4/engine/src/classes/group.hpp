#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include "model.hpp"
#include "transformation.hpp"
#include "../../lib/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Group{

private:
    vector<Model> models;
    vector<Transformation> transforms;
    vector<Group> subgroups;

public:
Group();
Group(vector<Model> models);
Group(vector<Transformation> transforms);

void parse_group(XMLElement* group_element);
vector<Model> get_models();
vector<Group> get_subgroups();
void set_models(vector<Model> models);
vector<Transformation> get_transforms();
void set_transforms(vector<Transformation> transforms);

};


#endif