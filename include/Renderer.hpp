#ifndef MLH_RENDERER_RENDERER_HPP
#define MLH_RENDERER_RENDERER_HPP

#include "CheckboxButton.hpp"
#include "QuadButton.hpp"
#include "SettingsData.hpp"
#include "Window.hpp"

namespace mlh {

class Renderer {
public:
  Renderer() { MainWindow = Window("Renderer"); }
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
  void addQuadButton(const QuadButton &ToAdd) {
    MainWindow.addQuadButton(ToAdd);
  }
  void addCheckboxButton(const CheckboxButton &ToAdd) {
    MainWindow.addCheckboxButton(ToAdd);
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
  SettingsData Settings = SettingsData();
};

} // namespace mlh

#endif
