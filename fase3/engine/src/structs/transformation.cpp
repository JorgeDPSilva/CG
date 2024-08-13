#include "transformation.hpp"

Transformation::Transformation() {}

Transformation::Transformation(float translate_x, float translate_y,
                               float translate_z, float rotate_angle,
                               float rotate_x, float rotate_y, float rotate_z,
                               float scale_x, float scale_y, float scale_z) {
  vector<float> translate = {translate_x, translate_y, translate_z};
  this->translate = translate;

  vector<float> rotate = {rotate_angle, rotate_x, rotate_y, rotate_z};
  this->rotate_angle = rotate;

  vector<float> scale = {scale_x, scale_y, scale_z};
  this->scale = scale;
}

vector<float> Transformation::get_translate() { return this->translate; }

vector<float> Transformation::get_rotate_angle() { return this->rotate_angle; }
vector<float> Transformation::get_rotate_time() { return this->rotate_time; }

vector<float> Transformation::get_scale() { return this->scale; }

string Transformation::get_transformation() { return this->transformation; }

bool Transformation::get_translation_align() { return this->translation_align; }

float Transformation::get_translation_time() { return this->translation_time; }

vector<vector<float>> Transformation::get_translationPoints() {
  return this->translation_Points;
}

void Transformation::set_translate(float x, float y, float z) {
  vector<float> translate = {x, y, z};
  this->translate = translate;
  this->transformation = "translate";
}

void Transformation::set_rotate(float angle, float x, float y, float z) {
  vector<float> rotate = {angle, x, y, z};
  this->rotate_angle = rotate;
  this->transformation = "rotate_angle";
}

void Transformation::set_scale(float x, float y, float z) {
  vector<float> scale = {x, y, z};
  this->scale = scale;
  this->transformation = "scale";
}

void Transformation::set_rotatetime(float time, float x, float y, float z) {
  vector<float> rotate_time = {time, x, y, z};
  this->rotate_time = rotate_time;
  this->transformation = "rotate_time";
}

void Transformation::parse_transformation(XMLElement *transformation_element) {
  string tag_name = transformation_element->Name();

  if (tag_name == "translate") {
    if (transformation_element->FirstChildElement()) {
      // Leitura dos atributos do elemento translate
      float time = transformation_element->FloatAttribute("time");
      float align = transformation_element->BoolAttribute("align");
      this->translation_time = time;
      this->translation_align = align;
      cout << "Time: " << this->translation_time
           << ", Align: " << this->translation_align << endl;

      // Iteração sobre os elementos <point> dentro de <translate>
      for (XMLElement *point_element =
               transformation_element->FirstChildElement();
           point_element; point_element = point_element->NextSiblingElement()) {
        float x = point_element->FloatAttribute("x");
        float y = point_element->FloatAttribute("y");
        float z = point_element->FloatAttribute("z");
        this->translation_Points.push_back({x, y, z});
        cout << "Point: (" << x << ", " << y << ", " << z << ")" << endl;
      }
      this->transformation = "translate_catmullrom";
    } else {
      // Leitura dos atributos do elemento translate
      float x = transformation_element->FloatAttribute("x");
      float y = transformation_element->FloatAttribute("y");
      float z = transformation_element->FloatAttribute("z");
      set_translate(x, y, z);
    }
  }
  if (tag_name == "rotate") {
        cout << "Rotate Element:" << endl;
        float angle;
        float time;
        XMLError angle_error =
            transformation_element->QueryFloatAttribute("angle", &angle);
        XMLError time_error =
            transformation_element->QueryFloatAttribute("time", &time);
        if (angle_error == XML_SUCCESS) {
        cout << "Fixed Rotation Angle: " << angle << endl;
        // Se houver um atributo de ângulo, aplicamos uma rotação fixa
        float x = transformation_element->FloatAttribute("x");
        float y = transformation_element->FloatAttribute("y");
        float z = transformation_element->FloatAttribute("z");
        set_rotate(angle, x, y, z);
        cout << "Rotation Axis: (" << x << ", " << y << ", " << z << ")" << endl;
        } else if (time_error == XML_SUCCESS) {
        cout << "Rotation over Time: " << endl;
        cout << "Time: " << time << endl;
        float time = transformation_element->FloatAttribute("time");
        float x = transformation_element->FloatAttribute("x");
        float y = transformation_element->FloatAttribute("y");
        float z = transformation_element->FloatAttribute("z");
        set_rotatetime(time, x, y, z);
        cout << "Rotation Axis: (" << x << ", " << y << ", " << z << ")" << endl;
        }
    }
    if (tag_name == "scale") {
      cout << "Scale Element:" << endl;
      float x = transformation_element->FloatAttribute("x");
      float y = transformation_element->FloatAttribute("y");
      float z = transformation_element->FloatAttribute("z");
      set_scale(x, y, z);
      cout << "Scale: (" << x << ", " << y << ", " << z << ")" << endl;
    }
}