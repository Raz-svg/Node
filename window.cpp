#include <glad/glad.h>
#include "window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
};

Window::Window() : window(nullptr), width(800), height(600) {}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

void Window::init(int w, int h) {
    width = w;
    height = h;

    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width,
        height,
        "Node Editor",
        nullptr,
        nullptr);

    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to init GLAD\n";
        return;
    }

    glViewport(0, 0, width, height);
}

void Window::update() {
    glfwPollEvents();  // handle input events
}

 const char* Window::ver_shader(const std::string& vertex_shader) {

    std::ifstream file(vertex_shader);

    if (!file) {
        std::cerr << "Failed to load vertex shader\n";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return (ver_shader_string = buffer.str()).c_str();

}


const char* Window::frag_shader(const std::string& fragment_shader) {
    std::ifstream file(fragment_shader);
    if (!file) {
        std::cerr << "Failed to load fragment shader\n";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return (frag_shader_string = buffer.str()).c_str();
}



void Window::render() {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);



    // draw your stuff here...

    float vertices[]={
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.5f,0.5f,0.0f,
    };

    unsigned int vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // function specially designed to copy used defined data into currently bound  buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 4th parameter
    // GL_STREAM_DRAW : set only once used at most a few time,
    // GL_STATIC_DRAW : set only once used many times,
    // GL_DYNAMIC_DRAW: changed a lot used many times

    //VERTEX SHADER INITIALIZATION
    const char *vertexShaderSource = ver_shader("vertex_shader.vert");

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader,1,&vertexShaderSource,nullptr);

    glCompileShader(vertexShader);

    int success;
    std::string infolog;

    //query a shader given a parameter
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);

    if (!success) {
        glGetShaderInfoLog(vertexShader,sizeof(infolog),nullptr,&infolog[0]);
        std::cout <<"ERROR::SHADER COMPILATION:FAILED\n"<<infolog << std::endl;
    }


    //FRAGMENT SHADER INITIALIZATION
    const char *fragmentShaderSource = frag_shader("fragment_shader.frag");

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader,1,&fragmentShaderSource,nullptr);

    glCompileShader(fragmentShader);

    //query a shader given a parameter
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);

    if (!success) {
        glGetShaderInfoLog(vertexShader,sizeof(infolog),nullptr,&infolog[0]);
        std::cout <<"ERROR::SHADER COMPILATION:FAILED\n"<<infolog << std::endl;
    }



    glfwSwapBuffers(window);
}

void Window::processInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::run() {
    init(width, height);
    while (!glfwWindowShouldClose(window)) {
        update();
        processInput();
        render();
    }
}
