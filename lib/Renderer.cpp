#include "Renderer.hpp"
#include "Window.hpp"

namespace mlh {

Renderer::Renderer() { MainWindow = Window(800, 600, "Renderer"); }

Renderer::~Renderer() { glfwTerminate(); }

void Renderer::runLoop() {
  start();

  while (!Close) {
    MainWindow.advance();

    Close = MainWindow.shouldClose();
  }
}

void Renderer::start() {
  Close = false;
  MainWindow.setShouldClose(false);
}

void Renderer::stop() {
  Close = true;
  MainWindow.setShouldClose(true);
}

} // namespace mlh
