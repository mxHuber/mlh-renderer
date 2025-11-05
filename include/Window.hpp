#ifndef MLH_RENDERER_WINDOW_HPP
#define MLH_RENDERER_WINDOW_HPP

#include "CheckboxButton.hpp"
#include "InitOpenGL.hpp"
#include "Keys.hpp"
#include "MouseButtons.hpp"
#include "Quad.hpp"
#include "QuadButton.hpp"
#include "RectangleRenderer.hpp"
#include "SettingsData.hpp"
#include "Shader.hpp"
#include <iostream>
#include <string>
#include <vector>

// glad must be included first
#include <glad/glad.h>
// then glfw afterwards
#include <GLFW/glfw3.h>

namespace mlh {

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
inline void framebuffer_size_callback(GLFWwindow *Window, int Width,
                                      int Height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, Width, Height);
}

inline void key_callback(GLFWwindow *Window, int Key, int Scancode, int Action,
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

inline void mouse_button_callback(GLFWwindow *Window, int Button, int Action,
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

inline static double XMousePos = 0.0;
inline static double YMousePos = 0.0;

inline void cursor_position_callback(GLFWwindow *window, double xpos,
                                     double ypos) {
  XMousePos = xpos;
  YMousePos = ypos;
}

// process all input: query GLFW whether relevant keys are pressed/released
// this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
inline void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

class Window {
public:
  Window() = default;
  Window(const char *Name) : Name(Name) {

    std::cout << "Initializing Glfw..." << std::endl;
    InitOpenGL::initializeGlfw();

    std::cout << "Creating window..." << std::endl;
    GlfwWindow = glfwCreateWindow(Settings.WindowWidth, Settings.WindowHeight,
                                  Name, NULL, NULL);

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

    // Initialize RectangleRenderer last, because it needs glad stuff
    Renderer = RectangleRenderer(Settings.WindowWidth, Settings.WindowHeight);
  }

  void advance() {
    processInput(GlfwWindow);
    glfwGetWindowSize(GlfwWindow, &Settings.WindowWidth,
                      &Settings.WindowHeight);

    // TODO: make all these checks in a more sensible manner. For example, move
    // each check to a function or something.
    for (auto &Curr : QuadButtons) {
      Renderer.addToBatch(Curr.getQuad());
      // glfw's mouse coords have the origin (0, 0) on the top left
      // (Height - YMousePos) / Height
      // so the origin is on the bottom left
      if (MouseButtons::LeftMousePressed) {
        if (Curr.isPosInBoundary(XMousePos / Settings.WindowWidth,
                                 (Settings.WindowHeight - YMousePos) /
                                     Settings.WindowHeight)) {
          Curr.onPress();
        }
      }
    }

    for (auto &Curr : CheckboxButtons) {
      Renderer.addToBatch(Curr.getQuad());
      // glfw's mouse coords have the origin (0, 0) on the top left
      // (Height - YMousePos) / Height
      // so the origin is on the bottom left
      if (LeftMousePressedLastFrame && !MouseButtons::LeftMousePressed) {
        if (Curr.isPosInBoundary(XMousePos / Settings.WindowWidth,
                                 (Settings.WindowHeight - YMousePos) /
                                     Settings.WindowHeight)) {
          Curr.onPress();
        }
      }

      LeftMousePressedLastFrame = false;
      if (MouseButtons::LeftMousePressed) {
        LeftMousePressedLastFrame = true;
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

  void setShouldClose(bool ToSet) {
    glfwSetWindowShouldClose(GlfwWindow, false);
  }

  bool shouldClose() { return glfwWindowShouldClose(GlfwWindow); }

  void setShader(const std::string &Vertex, const std::string &Fragment) {
    Renderer.setShader(Vertex, Fragment);
  }

  void setBackground(float TextureID) {
    Vertex A = {0.0f, 0.0f, 0.99999f, 1.0f, 1.0f,
                1.0f, 1.0f, 0.0f,     0.0f, TextureID};
    Vertex B = {1.0f, 0.0f, 0.99999f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,     0.0f, TextureID};
    Vertex C = {1.0f, 1.0f, 0.99999f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,     1.0f, TextureID};
    Vertex D = {0.0f, 1.0f, 0.99999f, 1.0f, 1.0f,
                1.0f, 1.0f, 0.0f,     1.0f, TextureID};
    Quad Background = {A, B, C, D};
    Quads.push_back(Background);
  }

  inline void addQuad(const Quad &ToAdd) { Quads.push_back(ToAdd); }
  inline void addQuadButton(const QuadButton &ToAdd) {
    QuadButtons.push_back(ToAdd);
  }
  inline void addCheckboxButton(const CheckboxButton &ToAdd) {
    CheckboxButtons.push_back(ToAdd);
  }
  inline void clearQuads() { Quads.clear(); }
  inline void clearButtons() { QuadButtons.clear(); }

  inline float createTexture(const std::string &Path) {
    return Renderer.createTexture(Path);
  };

private:
  SettingsData Settings;
  std::string Name;
  GLFWwindow *GlfwWindow = nullptr;
  bool LeftMousePressedLastFrame = false;

  RectangleRenderer Renderer = RectangleRenderer();
  std::vector<Quad> Quads = {};
  std::vector<QuadButton> QuadButtons = {};
  std::vector<CheckboxButton> CheckboxButtons = {};
};

} // namespace mlh

#endif
