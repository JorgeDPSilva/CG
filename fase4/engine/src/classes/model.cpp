#include "model.hpp"

Model::Model() {};

Model::Model(string newFile){
    this->file = newFile;
}

string Model::get_file(){
    return this->file;
}

int Model::get_numPoints(){
    return this->numPoints;
}

GLuint Model::get_points(){
    return this->vertexBuffer;;
}

GLuint Model::get_index(){
    return this->indexBuffer;
}

Colors Model::get_colors(){
    return this->colors;
}

void Model::set_file(string newFile) {
    this->file = newFile;
}

void Model::set_points(GLuint points){
    this->vertexBuffer = points;
}

void Model::set_index(GLuint index) {
    this->indexBuffer = index;
}

void Model::parse_model(XMLElement *model_elements){
    const char* file_attribute = model_elements->Attribute("file");
    
    if (file_attribute) {
        string file_attribute_str(file_attribute);
        set_file(file_attribute_str);
        readPointsFromFile();
        }

        for(XMLElement *model_element = model_elements->FirstChildElement();
            model_element; model_element = model_element->NextSiblingElement()){
            string model_tag_name = model_element->Name();
            if(model_tag_name == "color"){
                Colors new_color;
                new_color.parse_colors(model_element);
                this->colors = new_color;
                //cout << new_color.get_diffuse()[0] << endl;
        }
}
}


void Model::readPointsFromFile() {
    string filePath = "../generator/" + this->file;
    cout << "Caminho do Arquivo: " << filePath << endl; 
    ifstream file(filePath);
    
    vector<float> points;
    vector<int> triangleIndices;

    if (file.is_open()) {
        string line;
        int numPoints;
        
        // Ler o número de pontos
        getline(file, line);
        istringstream numPointsStream(line);
        if (!(numPointsStream >> numPoints)) {
            cerr << "Erro ao ler o número de pontos." << endl;
            return;
        }

        // Ler os pontos
        for (int i = 0; i < numPoints; i++) {
            getline(file, line);
            istringstream iss(line);
            float x, y, z;
            if (iss >> x >> y >> z) {
                points.push_back(x);
                points.push_back(y);
                points.push_back(z);
            } else {
                cerr << "Erro ao ler os pontos." << endl;
                return;
            }
        }
       
        // Ler o número de triângulos
        getline(file, line);
        int numTriangles;
        istringstream numTrianglesStream(line);
        if (!(numTrianglesStream >> numTriangles)) {
            cerr << "Erro ao ler o número de triângulos." << endl;
            return;
        }

        // ler a ordem pela qual temos que formar triangulos
        for (int i = 0; i < numTriangles; i++) {
            getline(file, line);
            istringstream triangleIndicesStream(line);
            int index1, index2, index3;
            if (triangleIndicesStream >> index1 >> index2 >> index3) {
                triangleIndices.push_back(index1);
                triangleIndices.push_back(index2);
                triangleIndices.push_back(index3);
            } else {
                cerr << "Erro ao ler as ordens para formar triângulos." << endl;
                return;
            }
        }
        this->numPoints = triangleIndices.size();
        file.close();
    } else {
        cerr << "Erro ao abrir o arquivo: " << this->file << endl;
    }

  // VBO para os vértice
  glGenBuffers(1, &(this->vertexBuffer));
  glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(),
               GL_STATIC_DRAW);

  // VBO para os índices
  glGenBuffers(1, &(this->indexBuffer));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * triangleIndices.size(),
               triangleIndices.data(), GL_STATIC_DRAW);
}