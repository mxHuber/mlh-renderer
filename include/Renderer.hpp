#ifndef MLH_RENDERER_HPP
#define MLH_RENDERER_HPP

#include "QuadButton.hpp"
#include "Window.hpp"

namespace mlh {

class Renderer {
public:
  Renderer() { MainWindow = Window(800, 600, "Renderer"); }
  ~Renderer() { glfwTerminate(); }

  void runLoop() {
    start();

    while (!Close) {
      MainWindow.advance();

      Close = MainWindow.shouldClose();
    }
  }

  void start() {
    Close = false;
    MainWindow.setShouldClose(false);
  }

  void stop() {
    Close = true;
    MainWindow.setShouldClose(true);
  }

  void addQuad(const Quad &ToAdd) { MainWindow.addQuad(ToAdd); }
  void addQuadButton(const QuadButton &ToAdd) { MainWindow.addButton(ToAdd); }
  void createQuadButton(const Quad &ToAdd) {
    MainWindow.addButton(
        std::move(QuadButton(ToAdd, MainWindow.getWidthReference(),
                             MainWindow.getHeightReference())));
  }

  void setShader(const std::string &Vertex, const std::string &Fragment) {
    MainWindow.setShader(Vertex, Fragment);
  }

  inline float createTexture(const std::string &Path) {
    return MainWindow.createTexture(Path);
  }

  inline void setBackground(float TextureID) {
    MainWindow.setBackground(TextureID);
  }

private:
  Window MainWindow = Window();
  bool Close = false;
};

} // namespace mlh

#endif
