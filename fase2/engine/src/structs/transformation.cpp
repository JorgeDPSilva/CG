#include "transformation.hpp"


Transformation::Transformation() {}

Transformation::Transformation(float translate_x, float translate_y, float translate_z, float rotate_angle, float rotate_x, float rotate_y, float rotate_z, float scale_x, float scale_y, float scale_z){
    vector<float> translate = {translate_x,translate_y,translate_z};
    this->translate = translate;

    vector<float> rotate = {rotate_angle,rotate_x,rotate_y,rotate_z};
    this->rotate = rotate;

    vector<float> scale = {scale_x,scale_y,scale_z};
    this->scale = scale;
}


vector<float> Transformation::get_translate(){
    return this->translate;
}

vector<float> Transformation::get_rotate(){
    return this->rotate;
}

vector<float> Transformation::get_scale(){
    return this->scale;
}

string Transformation::get_transformation(){
    return this->transformation;
}

void Transformation::set_translate(float x, float y, float z){
    vector<float> translate = {x,y,z};
    this->translate = translate;
    this->transformation = "translate";
}

void Transformation::set_rotate(float angle, float x, float y, float z){
    vector<float> rotate = {angle,x,y,z};
    this->rotate = rotate;
    this->transformation = "rotate";
}

void Transformation::set_scale(float x, float y, float z){
    vector<float> scale = {x,y,z};
    this->scale = scale;
    this->transformation = "scale";
}

void Transformation::parse_transformation(XMLElement *transformation_element){
    string tag_name = transformation_element->Name();
    float x = transformation_element->FloatAttribute("x");
    float y = transformation_element->FloatAttribute("y");
    float z = transformation_element->FloatAttribute("z");

    if (tag_name == "translate") {
        set_translate(x, y, z);
    } else if (tag_name == "scale") {
        set_scale(x, y, z);
    } else if (tag_name == "rotate") {
        float angle = transformation_element->FloatAttribute("angle");
        float x = transformation_element->FloatAttribute("x");
        float y = transformation_element->FloatAttribute("y");
        float z = transformation_element->FloatAttribute("z");
        set_rotate(angle,x,y,z);
    } 
}  

