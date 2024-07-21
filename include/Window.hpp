#ifndef EXREND2D_WINDOW_HPP
#define EXREND2D_WINDOW_HPP

#include <string>

// glad must be included first
#include <glad/glad.h>
// then glfw afterwards
#include <GLFW/glfw3.h>

class Window {
  //
public:
  Window(int Width, int Height, const char *Name);

  void advance();
  void draw();
  void setShouldClose(bool ToSet);
  bool shouldClose();

private:
  int Width;
  int Height;
  std::string Name;
  GLFWwindow *GlfwWindow;
};

#endif
