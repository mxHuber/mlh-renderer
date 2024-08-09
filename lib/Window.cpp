#include "Window.hpp"
#include "InitOpenGL.hpp"
#include "Quad.hpp"
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

void mouse_button_callback(GLFWwindow *Window, int Button, int Action,
                           int Mods) {
  if (true) {
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
  glfwSetCursorPosCallback(GlfwWindow, cursor_position_callback);

  std::cout << "Initializing glad..." << std::endl;
  InitOpenGL::initializeGlad();
  std::cout << "Initializing settings..." << std::endl;
  InitOpenGL::initializeSettings();

  // Initialize RectangleRenderer last, because it needs glad stuff
  RecShader = Shader(PathToVertexShader, PathToFragmentShader);
  Renderer = RectangleRenderer(RecShader, Width, Height);

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

  if (Counter > Threshold) {
    std::cout << "X: " << XMousePos << " Y: " << YMousePos << std::endl;
    std::cout << "Width: " << Width << " Height: " << Height << std::endl;
    std::cout << "x/w: " << XMousePos / Width << " y/h: " << YMousePos / Height
              << std::endl;
    Threshold += 100;
  }
  Counter++;

  int WindowXPos;
  int WindowYPos;
  glfwGetWindowPos(GlfwWindow, &WindowXPos, &WindowYPos);

  for (const auto &Curr : QuadButtons) {
    // glfw's mouse coords have the origin (0, 0) on the top left Why
    // though...?
    // (Height - YMousePos) / Height
    // so the user can set their object coords like a sensible human being with
    // the origin on the bottom left
    // Oh and OpenGL defines the viewspace between -1.0 and 1.0, because... why
    // not? :))
    if (Curr.checkClick(XMousePos / Width, (Height - YMousePos) / Height)) {
      std::cout << "Button was clicked!" << std::endl;
    }
    Renderer.addToBatch(Curr.getQuad());
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
