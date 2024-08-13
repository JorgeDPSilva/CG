#include "main.hpp"

Window window;
Camera camera;
Group group;



void drawModels() {
	
	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f,-100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f,-100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

	
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
    
	for (Model model : group.get_models()) {
        for (vector<int> triangleIndices : model.get_index()) {
            int index1 = triangleIndices[0]; 
            int index2 = triangleIndices[1]; 
            int index3 = triangleIndices[2];  


            vector<float> point1 = model.get_points()[index1];
            vector<float> point2 = model.get_points()[index2];
            vector<float> point3 = model.get_points()[index3];
			//x y z of each point 
            glVertex3f(point1[0], point1[1], point1[2]);
            glVertex3f(point2[0], point2[1], point2[2]);
            glVertex3f(point3[0], point3[1], point3[2]);
        }
    }
	
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
	vector<float> projection = camera.get_projection();
	gluPerspective(projection[0] ,ratio, projection[1] ,projection[2]);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	vector<float> position = camera.get_position();
    vector<float> look_at = camera.get_look_at();
    vector<float> up = camera.get_up();
	
	gluLookAt(position[0],position[1],position[2],
			look_at[0],look_at[1],look_at[2],
			up[0],up[1],up[2]);

	
	drawModels();
	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27) // Escape key
        exit(0);
}


//check if i can load the provided xml file
void readXML(char *argv){
    XMLDocument doc;
    if (doc.LoadFile(argv) == XML_SUCCESS) {
        cout << "XML file loaded successfully" << endl;
		XMLElement* root_element = doc.RootElement();
		for (XMLElement* child_element = root_element->FirstChildElement();child_element;child_element = child_element->NextSiblingElement()) {
				string child_name = child_element->Name();
				if (child_name == "window"){
                    	window.parse_window(child_element);
                }	if (child_name == "camera"){
                    	camera.parse_camera(child_element);
                }  	if (child_name == "group"){
						group.parse_group(child_element);
    			} 
		}
	}
	else {
        	cout << "Error loading XML file: " << argv << endl;
    		}
}

int main(int argc, char **argv) {
	if (argc != 2) {
    cout << "Invalid number of arguments" << endl;
    return -1;
  }
    
    readXML(argv[1]);

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(window.get_width(), window.get_height());
	glutCreateWindow("CG@DI-UM Grupo 11");
		
	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	

	
	// put here the registration of the keyboard callbacks
    glutKeyboardFunc(processNormalKeys);
    //glutSpecialFunc(processSpecialKeys);


    //OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	//enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}