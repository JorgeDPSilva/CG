#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;
float raio = 10;


void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}

void drawBules(){
	glColor3f(0.0f,0.0f,1.0f);
	float ang = 0.0f;
	float pontox;
	float pontoz;
	raio = 15;
	float quantos = 360/8;
	for(int i = 0; i<8; i ++){
		
		glPushMatrix();
		pontox = sin(ang)*raio;
		pontoz = cos(ang)*raio;
		
		glTranslatef(pontox,2.0f,pontoz);
		glRotatef((quantos*i)-90,0.0f,1.0f,0.0f);
		glutSolidTeapot(2);
		glPopMatrix();

		ang += 2*M_PI/8;
	}

	 // Adicionando um torus no meio dos teapots azuis
    glColor3f(1.0f, 1.0f, 0.0f);  // Cor amarela para o torus
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);  // Posição do torus no meio dos teapots
    glutSolidTorus(1.0, 3.0, 16, 16);  // Desenha o torus
    glPopMatrix();

	//teapots de fora a vermelho
	glColor3f(1.0f,0.0f,0.0f);
	ang = 0;
	raio = 35;
	quantos = 360/16;
	for(int i = 0; i<16; i ++){
		
		glPushMatrix();
		pontox = sin(ang)*raio;
		pontoz = cos(ang)*raio;
		
		glTranslatef(pontox,2.0f,pontoz);
		glRotatef(quantos*i,0.0f,1.0f,0.0f);
		glutSolidTeapot(2);
		glPopMatrix();

		ang += 2*M_PI/16;


	}


}


void drawThree(){
	float randx;
	float randz;
	for(int i = 0;i<500;i++){
		randx = (rand()%200) - 100;
		randz = (rand()%200) - 100;
		//desenhar arvores dentro do quadrado
		while(pow(randx,2)+pow(randz,2)<pow(50,2)){
			randx = (rand()%200) - 100;
			randz = (rand()%200) - 100;
		}
		glPushMatrix();
		
		glTranslatef(randx,0,randz);
		glRotated(-90, 1, 0, 0);
		glColor3ub(102,62,36);
		glutSolidCone(0.5,2,10,10);
		glTranslatef(0,0,2);
		glColor3ub(0,100,0);
		glutSolidCone(2,4,10,10);
		glPopMatrix();



	}


}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();
	
	// put code to draw scene in here
	glColor3f(1.0f,1.0f,1.0f);
	drawBules();
	drawThree();
	
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
