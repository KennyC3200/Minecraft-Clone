#include "window.h"

void Window::Init(glm::ivec2 size) {
    this->size = size;

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

void Window::Destroy() {
    glfwDestroyWindow(handle);
    glfwTerminate();
}

void Window::Update() {
    time_current = glfwGetTime();
    time_delta = time_current - time_previous;
    time_previous = time_current;
    fps = 1.0 / time_delta;

    glfwGetWindowSize(handle, &size.x, &size.y);
}

GLFWwindow* Window::GetHandle() {
    return handle;
}

glm::ivec2 Window::GetSize() {
    return size;
}

glm::vec2 Window::GetPixelUnit() {
    return 1.0f / glm::vec2(size);
}

float Window::GetFPS() {
    return fps;
}

float Window::GetTimeDelta() {
    return time_delta;
}
