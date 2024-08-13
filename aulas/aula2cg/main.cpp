#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float angle = 0.0f; // Initial rotation angle for the pyramid
float translateY = 0.0f;
float scaleFactor = 1.0f;

void drawPyramid() {
    // Frente
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);  // Vermelho
    glVertex3f(0.0, 1.0, 0.0); // Vertice superior
    glVertex3f(-1.0, -1.0, 1.0); // Vertice inferior esquerdo
    glVertex3f(1.0, -1.0, 1.0); // Vertice inferior direito
    glEnd();

    // Lado direito
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 1.0, 0.0);  // Verde
    glVertex3f(0.0, 1.0, 0.0); // Vertice superior
    glVertex3f(1.0, -1.0, 1.0); // Vertice inferior direito
    glVertex3f(1.0, -1.0, -1.0); // Vertice inferior esquerdo
    glEnd();

    // Lado traseiro
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0);  // Azul
    glVertex3f(0.0, 1.0, 0.0); // Vertice superior
    glVertex3f(1.0, -1.0, -1.0); // Vertice inferior esquerdo
    glVertex3f(-1.0, -1.0, -1.0); // Vertice inferior direito
    glEnd();

    // Lado esquerdo
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 0.0);  // Amarelo
    glVertex3f(0.0, 1.0, 0.0); // Vertice superior
    glVertex3f(-1.0, -1.0, -1.0); // Vertice inferior direito
    glVertex3f(-1.0, -1.0, 1.0); // Vertice inferior esquerdo
    glEnd();

    
    // Base
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 1.0, 1.0);  // Ciano

    // Primeiro triângulo
    glVertex3f(-1.0, -1.0, -1.0); // Inferior esquerdo
    glVertex3f(1.0, -1.0, -1.0);  // Inferior direito
    glVertex3f(1.0, -1.0, 1.0);   // Superior direito

    // Segundo triângulo
    glVertex3f(-1.0, -1.0, -1.0); // Inferior esquerdo
    glVertex3f(1.0, -1.0, 1.0);   // Superior direito
    glVertex3f(-1.0, -1.0, 1.0);  // Superior esquerdo

    glEnd();
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
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

    
    // put axis drawing in here
    glBegin(GL_LINES);
            // X axis in red
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-100.0f, 0.0f, 0.0f);
            glVertex3f( 100.0f, 0.0f, 0.0f);
            // Y Axis in Green
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, -100.0f, 0.0f);
            glVertex3f(0.0f,  100.0f, 0.0f);
            // Z Axis in Blue
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, -100.0f);
            glVertex3f(0.0f, 0.0f,  100.0f);
    glEnd();

    //put the geometric transformations here
    glRotatef(angle, 0.0f, 1.0f, 0.0f);  // Rotate around the Y-axis
    glTranslatef(0.0f, translateY, 0.0f);  // Translação ao longo do eixo Y
    glScalef(scaleFactor,scaleFactor,scaleFactor);

    //put pyramid drawing instructions here
    drawPyramid(); 
    

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27) // Escape key
        exit(0);
}

void processSpecialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            angle -= 5.0f;
            break;
        case GLUT_KEY_RIGHT:
            angle += 5.0f;
            break;
        //rever na aula
        case GLUT_KEY_UP:  
            translateY += 1.0f;
            break;
        case GLUT_KEY_DOWN:
            translateY -= 1.0f;    
            break;
        case GLUT_KEY_F1:
            scaleFactor += 1.0f;
        case GLUT_KEY_F2:
            scaleFactor -= 1.0f;
    }
    glutPostRedisplay();
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

	
// put here the registration of the keyboard callbacks
glutKeyboardFunc(processNormalKeys);
glutSpecialFunc(processSpecialKeys);


    //OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
