#include "lights.hpp"

Lights:: Lights() {}

vector<float> Lights::get_lights_directional(){
    return this->directional;
}

vector<float> Lights::get_lights_positional(){
    return this->positional;
}

string Lights::get_type(){
    return this->type;
}

float Lights::get_cutoff(){
    return this->cutoff;
}

void Lights::set_lights_directional(float dirX, float dirY, float dirZ){
    vector<float> dir = {dirX, dirY, dirZ,0.0};
    this->directional = dir;
    this->type = "directional";
}

void Lights::set_lights_positional(float posX, float posY, float posZ){
    vector<float> pos = {posX, posY, posZ,1.0};
    this->positional = pos;
    this->type = "positional";
}

void Lights::set_lights_spot(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float cutoff){
    vector<float> sposicional = {posX, posY, posZ,1.0};
    vector<float> sdirectional = {dirX, dirY, dirZ,0.0};
    this->positional = sposicional;
    this->directional = sdirectional;
    this->cutoff = cutoff;
    this->type = "spot";
}

void Lights::enable_light(int index){
    glEnable(GL_LIGHT0 + index);
}

void Lights::setup_light(int index){
    float dark[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4] = {1.0, 1.0, 1.0, 1.0};
    float black[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
    // light colors
glLightfv(GL_LIGHT0 + index, GL_AMBIENT, dark); 
glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, white); 
glLightfv(GL_LIGHT0 + index, GL_SPECULAR, white);
 // controls global ambient light
glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
}

void Lights::parse_lights(XMLElement *lights_elements,int index) {
const char* type = lights_elements->Attribute("type");
if (type) {
        string type_attribute_str(type);
if(type_attribute_str.compare("directional") == 0){  
float dirX = lights_elements->FloatAttribute("dirx");
float dirY = lights_elements->FloatAttribute("diry");
float dirZ = lights_elements->FloatAttribute("dirz");
set_lights_directional(dirX, dirY, dirZ);
enable_light(index);
setup_light(index);
} else if (type_attribute_str.compare("positional") == 0){
float posX = lights_elements->FloatAttribute("posx");
float posY = lights_elements->FloatAttribute("posy");
float posZ = lights_elements->FloatAttribute("posz");
set_lights_positional(posX, posY, posZ);
enable_light(index);
setup_light(index);
} else if (type_attribute_str.compare("spot") == 0){
    float posX = lights_elements->FloatAttribute("posx");
    float posY = lights_elements->FloatAttribute("posy");
    float posZ = lights_elements->FloatAttribute("posz");
    float dirX = lights_elements->FloatAttribute("dirx");
    float dirY = lights_elements->FloatAttribute("diry");
    float dirZ = lights_elements->FloatAttribute("dirz");
    float cutoff = lights_elements->FloatAttribute("cutoff");
    set_lights_spot(posX, posY, posZ, dirX, dirY, dirZ, cutoff);
    enable_light(index);
    setup_light(index);
    }
}

}


