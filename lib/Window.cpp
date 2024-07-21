#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *Window, int Width, int Height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, Width, Height);
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

Window::Window(int Width, int Height, const char *Name)
    : Width(Width), Height(Height), Name(Name) {
  GlfwWindow = glfwCreateWindow(Width, Height, Name, NULL, NULL);

  if (GlfwWindow == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    abort();
  }

  glfwMakeContextCurrent(GlfwWindow);
  glfwSetFramebufferSizeCallback(GlfwWindow, framebuffer_size_callback);
}

void Window::advance() {
  processInput(GlfwWindow);
  glfwSwapBuffers(GlfwWindow);
  glfwPollEvents();
}

void Window::draw() {
  while (!glfwWindowShouldClose(GlfwWindow)) {
    // input
    // -----
    processInput(GlfwWindow);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(GlfwWindow);
    glfwPollEvents();
  }
}

void Window::setShouldClose(bool ToSet) {
  glfwSetWindowShouldClose(GlfwWindow, false);
}

bool Window::shouldClose() { return glfwWindowShouldClose(GlfwWindow); }
