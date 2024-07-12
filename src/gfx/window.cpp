#include "window.hpp"

Window::Window() {}

Window::~Window() {}

void Window::init() {
    size.x = 1280;
    size.y = 720;

    if (!glfwInit()) {
        std::cout << "Error initializing GLFW\n";
        exit(1);
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle = glfwCreateWindow(
        size.x,
        size.y,
        "Minecraft",
        NULL,
        NULL
    );
    if (!handle) {
        glfwTerminate();
        std::cout << "Error initializing GLFW window\n";
        exit(1);
    }

    glfwMakeContextCurrent(handle);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Error initializing GLAD\n";
        exit(1);
    }
}

void Window::destroy() {
    glfwDestroyWindow(handle);
    glfwTerminate();
}
