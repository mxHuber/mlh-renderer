#include "Window.hpp"
#include "InitOpenGL.hpp"
#include "Keys.hpp"
#include "MouseButtons.hpp"
#include "Quad.hpp"
#include "Shader.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

namespace mlh {

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *Window, int Width, int Height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, Width, Height);
}

void key_callback(GLFWwindow *Window, int Key, int Scancode, int Action,
                  int mods) {
  if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS)
    glfwSetWindowShouldClose(Window, true);

  if (Key >= 0 && Key < 1024) {
    if (Action == GLFW_PRESS)
      Keys::keys[Key] = true;
    else if (Action == GLFW_RELEASE)
      Keys::keys[Key] = false;
  }
}

void mouse_button_callback(GLFWwindow *Window, int Button, int Action,
                           int Mods) {
  if (Button == GLFW_MOUSE_BUTTON_LEFT && Action == GLFW_PRESS) {
    MouseButtons::LeftMousePressed = true;
  } else if (Button == GLFW_MOUSE_BUTTON_LEFT && Action == GLFW_RELEASE) {
    MouseButtons::LeftMousePressed = false;
  }
  if (Button == GLFW_MOUSE_BUTTON_RIGHT) {
    MouseButtons::RightMousePressed = true;
  } else if (Button == GLFW_MOUSE_BUTTON_RIGHT && Action == GLFW_RELEASE) {
    MouseButtons::RightMousePressed = false;
  }
}

double XMousePos = 0.0;
double YMousePos = 0.0;

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
  XMousePos = xpos;
  YMousePos = ypos;
}

// process all input: query GLFW whether relevant keys are pressed/released
// this frame and react accordingly
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
  glfwSetKeyCallback(GlfwWindow, key_callback);
  glfwSetMouseButtonCallback(GlfwWindow, mouse_button_callback);
  glfwSetCursorPosCallback(GlfwWindow, cursor_position_callback);

  std::cout << "Initializing glad..." << std::endl;
  InitOpenGL::initializeGlad();
  std::cout << "Initializing settings..." << std::endl;
  InitOpenGL::initializeSettings();

  // Shader can only be created if a context current is set
  // That is why Renderer is only fully set here, as it has a Shader class
  // variable
  Renderer = RectangleRenderer(800, 600);

  // Initialize RectangleRenderer last, because it needs glad stuff
  Renderer = RectangleRenderer(Width, Height);

  Vertex TestA = {0.2f, 0.2f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f};
  Vertex TestB = {0.4f, 0.2f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f};
  Vertex TestC = {0.4f, 0.4f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};
  Vertex TestD = {0.2f, 0.4f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};

  Quad Test = {TestA, TestB, TestC, TestD};

  QuadButton Button1 = QuadButton(std::move(Test), Width, Height);

  QuadButtons.push_back(Button1);
}

int Counter = 0;
int Threshold = 100;

void Window::advance() {
  processInput(GlfwWindow);

  for (const auto &Curr : QuadButtons) {
    Renderer.addToBatch(Curr.getQuad());
    // glfw's mouse coords have the origin (0, 0) on the top left
    // (Height - YMousePos) / Height
    // so the origin is on the bottom left
    if (MouseButtons::LeftMousePressed) {
      if (Curr.checkBounds(XMousePos / Width, (Height - YMousePos) / Height)) {
        std::cout << "Button was clicked!" << std::endl;
      }
    }
  }

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

} // namespace mlh
