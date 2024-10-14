#ifndef MLH_RENDERER_HPP
#define MLH_RENDERER_HPP

#include "Window.hpp"

namespace mlh {

class Renderer {
public:
  Renderer();
  ~Renderer();

  void runLoop();
  void stop();
  void start();

  void addQuad(const Quad &ToAdd) { MainWindow.addQuad(ToAdd); }
  void setShader(const std::string &Vertex, const std::string &Fragment);

private:
  Window MainWindow = Window();
  bool Close = false;
};

} // namespace mlh

#endif
