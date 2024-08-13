#include "colors.hpp"

Colors::Colors() {
  vector<float> diffuse = {200, 200, 200};
  this->diffuse = diffuse;
  vector<float> ambient = {50, 50, 50};
  this->ambient = ambient;
  vector<float> specular = {0, 0, 0};
  this->specular = specular;
  vector<float> emissive = {0, 0, 0};
  this->emissive = emissive;
  this->shininess = 0;
}

Colors::Colors(float diffuse_r, float diffuse_g, float diffuse_b,
               float ambient_r, float ambient_g, float ambient_b,
               float specular_r, float specular_g, float specular_b,
               float emissive_r, float emissive_g, float emissive_b,
               float value) {
  vector<float> diffuse = {diffuse_r, diffuse_g, diffuse_b};
  this->diffuse = diffuse;
  vector<float> ambient = {ambient_r, ambient_g, ambient_b};
  this->ambient = ambient;
  vector<float> specular = {specular_r, specular_g, specular_b};
  this->specular = specular;
  vector<float> emissive = {emissive_r, emissive_g, emissive_b};
  this->emissive = emissive;
  this->shininess = value;
}

vector<float> Colors::get_diffuse() { 
  return this->diffuse; 
  }

vector<float> Colors::get_ambient() { 
  return this->ambient; 
  }

vector<float> Colors::get_specular() { 
  return this->specular; 
  }

vector<float> Colors::get_emissive() { 
  return this->emissive; 
  }

float Colors::get_shininess() { 
  return this->shininess; 
  }



void Colors::set_diffuse(float r, float g, float b) {
  vector<float> diffuse = {r, g, b};
  this->diffuse = diffuse;
}

void Colors::set_ambient(float r, float g, float b) {
  vector<float> ambient = {r, g, b};
  this->ambient = ambient;
}

void Colors::set_specular(float r, float g, float b) {
  vector<float> specular = {r, g, b};
  this->specular = specular;
}

void Colors::set_emissive(float r, float g, float b) {
  vector<float> emissive = {r, g, b};
  this->emissive = emissive;
}

void Colors::set_value(float value) { this->shininess = value; }

void Colors::parse_colors(XMLElement *colors_element) {

  // Iteração sobre os elementos dentro de <color>
  for (XMLElement *color_element = colors_element->FirstChildElement();
       color_element; color_element = color_element->NextSiblingElement()) {
    string color_tag_name = color_element->Name();
    if (color_tag_name == "diffuse") {
      float r = color_element->FloatAttribute("R")/255;
      float g = color_element->FloatAttribute("G")/255;
      float b = color_element->FloatAttribute("B")/255;
      set_diffuse(r, g, b);
    } else if (color_tag_name == "ambient") {
      float r = color_element->FloatAttribute("R")/255;
      float g = color_element->FloatAttribute("G")/255;
      float b = color_element->FloatAttribute("B")/255;
      set_ambient(r, g, b);
    } else if (color_tag_name == "specular") {
      float r = color_element->FloatAttribute("R")/255;
      float g = color_element->FloatAttribute("G")/255;
      float b = color_element->FloatAttribute("B")/255;
      set_specular(r, g, b);
    } else if (color_tag_name == "emissive") {
      float r = color_element->FloatAttribute("R")/255;
      float g = color_element->FloatAttribute("G")/255;
      float b = color_element->FloatAttribute("B")/255;
      set_emissive(r, g, b);
    } else {
      float value = color_element->FloatAttribute("value");
      set_value(value);
    }
  }
}