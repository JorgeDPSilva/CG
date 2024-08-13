#include "group.hpp"


Group::Group() {};

Group::Group(vector<Model> models){
    this->models = models;
}

Group::Group(vector<Transformation> transforms){
    this->transforms = transforms;
}

vector<Model> Group::get_models(){
    return this->models;
}

vector<Group> Group::get_subgroups(){
    return this->subgroups;
}

void Group::set_models(vector<Model> models){
  this->models = models;
}


vector<Transformation> Group::get_transforms() {
    return this->transforms;
}

void Group::set_transforms(vector<Transformation> transforms) {
    this->transforms = transforms;
}


void Group::parse_group(XMLElement* group_element) {
    for (XMLElement* group_children = group_element->FirstChildElement(); group_children; group_children = group_children->NextSiblingElement()) {
        string child_name = group_children->Name();

        if(child_name == "models") {
            for (XMLElement* model_element = group_children->FirstChildElement();model_element;model_element = model_element->NextSiblingElement()){
                Model new_model;
                new_model.parse_model(model_element);
                this->models.push_back(new_model); // mutiple models for the example case 1_5;
            }
        } else if (child_name == "transform") {
            for (XMLElement* transform_element = group_children->FirstChildElement(); transform_element; transform_element = transform_element->NextSiblingElement()){
                Transformation new_transform;
                new_transform.parse_transformation(transform_element);
                this->transforms.push_back(new_transform);
            }
        } else if (child_name == "group"){
            Group new_group;
            new_group.parse_group(group_children);
            subgroups.push_back(new_group);
        }
    }
}
