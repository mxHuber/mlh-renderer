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
  void addButton(const QuadButton &ToAdd) { MainWindow.addButton(ToAdd); }
  void setShader(const std::string &Vertex, const std::string &Fragment);
  inline float createTexture(const std::string &Path) {
    return MainWindow.createTexture(Path);
  };
  inline void setBackground(float TextureID) {
    MainWindow.setBackground(TextureID);
  }

private:
  Window MainWindow = Window();
  bool Close = false;
};

} // namespace mlh

#endif
