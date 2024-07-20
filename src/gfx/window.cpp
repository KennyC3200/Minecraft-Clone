#include "window.hpp"

Window::Window() {}

Window::~Window() {}

void Window::init() {
    size = {1440, 900};

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

    // initialize time variables
    time_current = glfwGetTime();
    time_previous = time_current;
    time_delta = 0.0;
}

void Window::destroy() {
    glfwDestroyWindow(handle);
    glfwTerminate();
}

void Window::update() {
    time_current = glfwGetTime();
    time_delta = time_current - time_previous;
    time_previous = time_current;
    fps = 1.0 / time_delta;

    glfwGetWindowSize(handle, &size.x, &size.y);
}
