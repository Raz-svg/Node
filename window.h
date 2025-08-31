#ifndef NODE_WINDOW_H
#define NODE_WINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>


class Window {
public:
    Window();
    ~Window();

    void init(int width, int height);
    void update();
    void render();
    void run();
    void processInput();
    const char* ver_shader(const std::string &vertex_shader);
    const char *frag_shader(const std::string &fragment_shader);

private:
    GLFWwindow* window;
    int width, height;
    std::string ver_shader_string;
    std::string frag_shader_string;
};

#endif
