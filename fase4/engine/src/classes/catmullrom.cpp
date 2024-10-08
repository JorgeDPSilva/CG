#include "catmullrom.hpp"

void buildRotMatrix(float *x, float *y, float *z, float *m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}


void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

void normalize(float *a) {

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

	// catmull-rom matrix
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};
			
	// Compute A = M * P
    float px[4] = {p0[0], p1[0], p2[0], p3[0]};
    float py[4] = {p0[1], p1[1], p2[1], p3[1]};
    float pz[4] = {p0[2], p1[2], p2[2], p3[2]};
    float ax[4], ay[4], az[4];
    multMatrixVector((float *)m, px, ax);
    multMatrixVector((float *)m, py, ay);
    multMatrixVector((float *)m, pz, az);
    
    // Compute pos = T * A
    float tMatrix[4] = {powf(t,3), powf(t,2), t, 1};
    pos[0] = tMatrix[0] * ax[0] + tMatrix[1] * ax[1] + tMatrix[2] * ax[2] + tMatrix[3] * ax[3];
    pos[1] = tMatrix[0] * ay[0] + tMatrix[1] * ay[1] + tMatrix[2] * ay[2] + tMatrix[3] * ay[3];
    pos[2] = tMatrix[0] * az[0] + tMatrix[1] * az[1] + tMatrix[2] * az[2] + tMatrix[3] * az[3];
    
    // Compute deriv = T' * A
    float tPrimeMatrix[4] = {3*powf(t,2), 2 * t, 1, 0};
    deriv[0] = tPrimeMatrix[0] * ax[0] + tPrimeMatrix[1] * ax[1] + tPrimeMatrix[2] * ax[2] + tPrimeMatrix[3] * ax[3];
    deriv[1] = tPrimeMatrix[0] * ay[0] + tPrimeMatrix[1] * ay[1] + tPrimeMatrix[2] * ay[2] + tPrimeMatrix[3] * ay[3];
    deriv[2] = tPrimeMatrix[0] * az[0] + tPrimeMatrix[1] * az[1] + tPrimeMatrix[2] * az[2] + tPrimeMatrix[3] * az[3];
}

// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, vector<vector<float>> translation_points) {

    int POINT_COUNT = translation_points.size();
	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4]; 
	indices[0] = (index + POINT_COUNT-1)% POINT_COUNT;	
	indices[1] = (indices[0]+1) % POINT_COUNT;
	indices[2] = (indices[1]+1) % POINT_COUNT; 
	indices[3] = (indices[2]+1) % POINT_COUNT;

	getCatmullRomPoint(t, translation_points[indices[0]].data(), translation_points[indices[1]].data(), translation_points[indices[2]].data(), translation_points[indices[3]].data(), pos, deriv);
}


void renderCatmullRomCurve(vector<vector<float>> translation_points) {
    float pos[3]; // coordenadas de cada posição (coordenadas do P0,P1...)
    float deriv[3]; //coordenadas cada posicao com usamos o vetor das derivadas
    glBegin(GL_LINE_LOOP);
    for (float t = 0; t < 1.0f; t += 0.01f) {
        getGlobalCatmullRomPoint(t, pos, deriv,translation_points);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
}


void drawCatmullRomCurve(float t, vector<vector<float>> translation_points,bool align){
    float pos[3]; // coordenadas de cada posição (coordenadas do P0,P1...)
    float deriv[3]; //coordenadas cada posiçao com usamos o vetor das derivadas
    
    // Desenhar a curva em branco
    glColor3f(1.0f, 1.0f, 1.0f);
	renderCatmullRomCurve(translation_points);
    
    getGlobalCatmullRomPoint(t, pos, deriv,translation_points); //t passado no xml
    
    // Aplicar a transformação de translação para mover o objeto para a posição na curva
     glTranslatef(pos[0], pos[1], pos[2]);
    if(align){
        float x[3] = { deriv[0], deriv[1], deriv[2] };
	    float y[3] = { 0.0f, 1.0f, 0.0f };
	    float z[3];
        normalize(x);
		cross(x, y, z);
		normalize(z);
		cross(z, x, y);
		normalize(y);
		normalize(deriv);

		float m[16];

		buildRotMatrix(x, y, z, m);
		glMultMatrixf(m);
    }
}


