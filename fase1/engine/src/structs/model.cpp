#include "model.hpp"

Model::Model() {};

Model::Model(string newFile){
    this->file = newFile;
}


string Model::get_file(){
    return this->file;
}

vector<vector <float>> Model::get_points(){
    return this->points;
}

vector<vector <int>> Model::get_index(){
    return this->index;
}

void Model::set_file(string newFile) {
    this->file = newFile;
}

void Model::set_points(vector<vector <float>> points){
    this->points = points;
}

void Model::set_index(vector<vector <int>> index) {
    this->index = index;
}

void Model::parse_model(XMLElement *model_elements){
    const char* file_attribute = model_elements->Attribute("file");
    
    if (file_attribute) {
        string file_attribute_str(file_attribute);
        set_file(file_attribute_str);
        readPointsFromFile();
        }
}


void Model::readPointsFromFile() {
    string filePath = "../generator/" + this->file;
    cout << "Caminho do Arquivo: " << filePath << endl; 
    ifstream file(filePath);
    
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
                vector<float> point = {x, y, z};
                this->points.push_back(point);
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
                vector<int> triangleIndices = {index1, index2, index3};
                this->index.push_back(triangleIndices);
            } else {
                cerr << "Erro ao ler as ordens para formar triângulos." << endl;
                return;
            }
        }

        file.close();
    } else {
        cerr << "Erro ao abrir o arquivo: " << this->file << endl;
    }
}