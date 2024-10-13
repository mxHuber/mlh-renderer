#ifndef MLH_RENDERER_WINDOW_HPP
#define MLH_RENDERER_WINDOW_HPP

#include "Quad.hpp"
#include "QuadButton.hpp"
#include "RectangleRenderer.hpp"
#include <string>
#include <vector>

// glad must be included first
#include <glad/glad.h>
// then glfw afterwards
#include <GLFW/glfw3.h>

namespace mlh {

class Window {
public:
  Window() = default;
  Window(int Width, int Height, const char *Name);

  void advance();
  void setShouldClose(bool ToSet);
  bool shouldClose();

  inline void addQuad(const Quad &ToAdd) { Quads.push_back(ToAdd); }
  inline void clearQuads() { Quads.clear(); }

private:
  int Width = 800;
  int Height = 600;
  std::string Name;
  GLFWwindow *GlfwWindow = nullptr;

  RectangleRenderer Renderer = RectangleRenderer();
  std::vector<Quad> Quads = {};
  std::vector<QuadButton> QuadButtons = {};
};

} // namespace mlh

#endif
