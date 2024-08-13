#include "main.hpp"

Window window;
Camera camera;
Group group;
int timebase;
float frame = 0;



// desenhar o model atraves dos vbos
void drawModel(Model model) {
  // Set buffer active and define the semantics
	glBindBuffer(GL_ARRAY_BUFFER, model.get_points());
	glVertexPointer(3, GL_FLOAT, 0, 0);
  // Draw the model using the index buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.get_index());
  glDrawElements(GL_TRIANGLES, model.get_numPoints() * 3, GL_UNSIGNED_INT, NULL);
}
  


void drawModels(Group group) {
  glPushMatrix();

  for (Transformation transform : group.get_transforms()) {
    string transformation = transform.get_transformation();

    if (transformation == "translate") {
      vector<float> translate = transform.get_translate();
      glTranslatef(translate[0], translate[1], translate[2]);
    } else if(transformation == "translate_catmullrom"){
      vector<vector<float>> translation_points = transform.get_translationPoints();
      int t_time = transform.get_translation_time();
      float time = glutGet(GLUT_ELAPSED_TIME) % (int)(t_time * 1000);
      float tempo = time / (t_time * 1000);
      drawCatmullRomCurve(tempo, translation_points, transform.get_translation_align());
    }
    else if (transformation == "scale") {
      vector<float> scale = transform.get_scale();
      glScalef(scale[0], scale[1], scale[2]);
    } else if (transformation == "rotate_angle") {
      vector<float> rotate = transform.get_rotate_angle();
      glRotatef(rotate[0], rotate[1], rotate[2], rotate[3]);
    } else if (transformation == "rotate_time"){
      vector<float> rotate_time = transform.get_rotate_time();
      float angle = 360.0f / (rotate_time[0] * 1000);
      float time = glutGet(GLUT_ELAPSED_TIME);
      glRotatef(angle * time, rotate_time[1], rotate_time[2], rotate_time[3]);

    }
  }

  for (Model model : group.get_models()) {
    drawModel(model);
  }

  for (Group subgroup : group.get_subgroups()) {
    drawModels(subgroup);
  }

  glPopMatrix();
}

void drawAxis() {
  glBegin(GL_LINES);
  // X axis in red
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-100.0f, 0.0f, 0.0f);
  glVertex3f(100.0f, 0.0f, 0.0f);
  // Y Axis in Green
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, -100.0f, 0.0f);
  glVertex3f(0.0f, 100.0f, 0.0f);
  // Z Axis in Blue
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, -100.0f);
  glVertex3f(0.0f, 0.0f, 100.0f);
  glEnd();
}

void changeSize(int w, int h) {
  // Prevent a divide by zero, when window is too short
  // (you cant make a window with zero width).
  if (h == 0)
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
  gluPerspective(projection[0], ratio, projection[1], projection[2]);

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

  gluLookAt(position[0], position[1], position[2],
           look_at[0], look_at[1],look_at[2], 
           up[0], up[1], up[2]);

  glPolygonMode(GL_FRONT, GL_LINE);

  // Calculate FPS
  frame++;
  int time = glutGet(GLUT_ELAPSED_TIME);
  if (time - timebase > 1000) {
    float fps = frame * 1000.0 / (time - timebase);
    timebase = time;
    frame = 0;
    // Update window title with FPS
    char s[30];
    sprintf(s, "FPS: %4.2f", fps);
    glutSetWindowTitle(s);
  }

  drawAxis();

  glColor3f(1.0f, 1.0f, 1.0f);

  drawModels(group);

  // End of frame
  glutSwapBuffers();
}

// write function to process keyboard events
void processNormalKeys(unsigned char key, int x, int y) {
  if (key == 27) // Escape key
    exit(0);
}

// check if i can load the provided xml file
void readXML(char *argv) {
  XMLDocument doc;
  if (doc.LoadFile(argv) == XML_SUCCESS) {
    cout << "XML file loaded successfully" << endl;
    XMLElement *root_element = doc.RootElement();
    for (XMLElement *child_element = root_element->FirstChildElement();
         child_element; child_element = child_element->NextSiblingElement()) {
      string child_name = child_element->Name();
      if (child_name == "window") {
        window.parse_window(child_element);
      }
      if (child_name == "camera") {
        camera.parse_camera(child_element);
      }
      if (child_name == "group") {
        group.parse_group(child_element);
      }
    }
  } else {
    cout << "Error loading XML file: " << argv << endl;
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Invalid number of arguments" << endl;
    return -1;
  }

  // init GLUT and the window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(window.get_width(), window.get_height());
  timebase = glutGet(GLUT_ELAPSED_TIME);
  glutCreateWindow("CG@DI-UM Grupo 11");

  // Required callback registry
  glutDisplayFunc(renderScene);
  glutIdleFunc(renderScene);
  glutReshapeFunc(changeSize);

  // put here the registration of the keyboard callbacks
  glutKeyboardFunc(processNormalKeys);
// glutSpecialFunc(processSpecialKeys);

// init GLEW
#ifndef __APPLE__
  glewInit();
#endif

  // OpenGL settings
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  readXML(argv[1]);
  // enter GLUT's main cycle
  glutMainLoop();

  return 1;
}