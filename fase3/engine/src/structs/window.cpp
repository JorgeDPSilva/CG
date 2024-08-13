#include "window.hpp"

Window::Window() {}

Window::Window(int width, int height) {
  this->width = width;
  this->height = height;
}

int Window::get_width(){
    return this->width;
}

int Window::get_height(){
    return this->height;
}

void Window::set_width(int width){
    this->width = width;
}

void Window::set_height(int height){
    this->height = height;
}



void Window::parse_window(XMLElement *window_elements) {

int width = window_elements->IntAttribute("width");

int height = window_elements->IntAttribute("height");

  if (width > 0 && height > 0) {
    set_width(width);  
    set_height(height);
    };
}