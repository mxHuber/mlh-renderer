#include "Window.hpp"
#include "InitOpenGL.hpp"
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
  std::cout << "Initializing Glfw..." << std::endl;
  InitOpenGL::initializeGlfw();

  std::cout << "Creating window..." << std::endl;
  GlfwWindow = glfwCreateWindow(Width, Height, Name, NULL, NULL);

  if (GlfwWindow == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    abort();
  }

  // glfwMakeContextCurrent must be called before initializing glad
  glfwMakeContextCurrent(GlfwWindow);
  glfwSetFramebufferSizeCallback(GlfwWindow, framebuffer_size_callback);

  std::cout << "Initializing glad..." << std::endl;
  InitOpenGL::initializeGlad();
  std::cout << "Initializing settings..." << std::endl;
  InitOpenGL::initializeSettings();

  // Initialize RectangleRenderer last, because it needs glad stuff
  RecShader = Shader(PathToVertexShader, PathToFragmentShader);
  Renderer = RectangleRenderer(RecShader);
}

void Window::advance() {
  processInput(GlfwWindow);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (const auto &Curr : Quads) {
    Renderer.addToBatch(Curr);
  }

  Renderer.drawBatch();

  glfwSwapBuffers(GlfwWindow);
  glfwPollEvents();
}

void Window::setShouldClose(bool ToSet) {
  glfwSetWindowShouldClose(GlfwWindow, false);
}

bool Window::shouldClose() { return glfwWindowShouldClose(GlfwWindow); }
