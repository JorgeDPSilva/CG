#include "patches.hpp"

float Bezier_Matrix[4][4] = {{-1.0f, 3.0f, -3.0f, 1.0},
                             {3.0f, -6.0f, 3.0f, 0.0f},
                             {-3.0f, 3.0f, 0.0f, 0.0f},
                             {1.0f, 0.0f, 0.0f, 0.0f}};

void multMatrixMatrix(float matrix1[4][4], float matrix2[4][4],
                      float final_matrix[4][4]) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      final_matrix[i][j] = 0;
      for (int k = 0; k < 4; k++)
        final_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
    }
}

void multMatrix44Matrix41(float matrix1[4][4], float matrix2[4][1],
                          float vector[4]) {
  for (int i = 0; i < 4; i++) {
    vector[i] = 0; // Inicialize o vetor[i] antes de começar a somar os produtos
    for (int k = 0; k < 4; k++) {
      vector[i] += matrix1[i][k] * matrix2[k][0];
    }
  }
}

float multVectorVector(float vector1[], float vector2[]) {
  return vector1[0] * vector2[0] + vector1[1] * vector2[1] +
         vector1[2] * vector2[2] + vector1[3] * vector2[3];
}

/* p(u,v)= [u^3 u^2 u 1]  bezier matriz * matriz aixs(x,y,z) * M(transposta que
   é igual) * [v^3 v^2 v 1 ]*/
float bezier(float u, float v, float default_matrix[4][4],
             float matrix_axis[4][4]) {

  float tempVector[4];
  float tempMatrix1[4][4];
  float tempMatrix2[4][4];

  float u_vector[4] = {u * u * u, u * u, u, 1};
  float v_matrix[4][1] = {{v * v * v}, {v * v}, {v}, {1}};

  // bezier_matrix * matrix_axis   = tempMatrix1
  multMatrixMatrix(default_matrix, matrix_axis, tempMatrix1);

  // tempMatrix1 * M = tempMatrix2
  multMatrixMatrix(tempMatrix1, default_matrix, tempMatrix2);

  // tempMatrix2 * v = tempVector
  multMatrix44Matrix41(tempMatrix2, v_matrix, tempVector);

  // tempvector * u = result
  return multVectorVector(tempVector, u_vector);
}

void readPatchFile(string filename, int tesselation, string final_filename) {
  // Abrir o ficheiro
  ifstream file(filename);
  if (file.is_open()) {
    string line;
    int num_patches;
    vector<vector<int>> patches;
    vector<Point> points;

    vector<Point> finalpoints;
    vector<Index> finalindices;

    // Necessário calcular para cada componente (x,y,z)
    float matrix_x[4][4];
    float matrix_y[4][4];
    float matrix_z[4][4];

    // Ler o número de patches
    getline(file, line);
    istringstream numPatchesStream(line);
    if (!(numPatchesStream >> num_patches)) {
      cerr << "Erro ao ler o número de pontos." << endl;
    }

    // Ler os patches
    for (int i = 0; i < num_patches; i += 1) {
      if (getline(file, line)) {
        stringstream ss(line);
        string s;

        vector<int> patch;
        while (getline(ss, s, ',')) {
          patch.push_back(stoi(s));
        }
        patches.push_back(patch);

      } else {
        cerr << "Erro ao ler os pontos." << endl;
      }
    }

    // Ler o número de pontos
    getline(file, line);
    int numPoints;
    istringstream numPointsStream(line);
    if (!(numPointsStream >> numPoints)) {
      cerr << "Erro ao ler o número de pontos" << endl;
    }

    // Ler os pontos
    for (int j = 0; j < numPoints; j++) {
      if (getline(file, line)) {
        stringstream ss(line);
        string s;
        vector<float> tempvector;

        while (getline(ss, s, ',')) {
          tempvector.push_back(stof(s));
        }

        points.push_back(Point(tempvector[0], tempvector[1], tempvector[2]));

      } else {
        cerr << "Erro ao ler os pontos." << endl;
      }
    }

    // Calcular as matrizes de cada componente(x,y,z)
    for (vector<int> patch : patches) {
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          int control_index =
              patch[i * 4 + j]; // Índice do ponto de controle no vetor points
          matrix_x[j][i] = points[control_index].getX();
          matrix_y[j][i] = points[control_index].getY();
          matrix_z[j][i] = points[control_index].getZ();
        }
      }

      // Calcular os triangulos com o bezier
      for (int i = 0; i <= tesselation; i++) {
        for (int j = 0; j <= tesselation; j++) {
          float u = i / (float)tesselation;
          float v = j / (float)tesselation;

          float x1 = bezier(u, v, Bezier_Matrix, matrix_x);
          float y1 = bezier(u, v, Bezier_Matrix, matrix_y);
          float z1 = bezier(u, v, Bezier_Matrix, matrix_z);
          finalpoints.push_back(Point(x1, y1, z1));
        }
      }
    }

// calcular os indices
int num_indexes_per_patch = (tesselation + 1) * (tesselation + 1);
// Para cada patch
for (int patch_index = 0; patch_index < num_patches; patch_index++) {
  // Calcular o índice inicial deste patch
  int patch_offset = patch_index * num_indexes_per_patch;

  // Para cada ponto na tesselação do patch
  for (int u = 0; u < tesselation; u++) {
    for (int v = 0; v < tesselation; v++) {
      // Calcular os índices dos pontos deste triângulo
      int p1_x = patch_offset + (tesselation + 1) * u + v;
      int p1_y = patch_offset + (tesselation + 1) * (u + 1) + v;
      int p1_z = p1_x + 1;

      int p2_y = p1_y + 1;
      
      // Adicionar os triângulos na ordem correta
      finalindices.push_back(Index(p1_x, p1_y, p1_z));
      finalindices.push_back(Index(p1_y, p2_y, p1_z));
    }
  }
}
    // Fechar o ficheiro
    file.close();
    create3d(final_filename, finalpoints, finalindices);
  } else {
    cerr << "Erro ao abrir o ficheiro." << endl;
  }
}
