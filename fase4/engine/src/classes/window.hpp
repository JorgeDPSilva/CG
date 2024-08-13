#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include "../../lib/tinyxml2.h"

using namespace tinyxml2;

class Window {

private:
int width;
int height;

public:
Window ();

Window(int width,int height);
void parse_window(XMLElement *window_elements);

int get_width();
int get_height();
void set_width(int width);
void set_height(int height);


};
#endif