#include "group.hpp"


Group::Group() {};

Group::Group(vector<Model> models){
    this->models = models;
}

vector<Model> Group::get_models(){
    return this->models;
}

void Group::set_models(vector<Model> models){
  this->models = models;
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
            }
        }
    cout << "Tamanho do vetor: " << this->models.size() << endl;
} 