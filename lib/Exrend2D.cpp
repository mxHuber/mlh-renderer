#include "Exrend2D.hpp"

Exrend2D::Exrend2D() {}

Exrend2D::~Exrend2D() { glfwTerminate(); }

void Exrend2D::runLoop() {
  start();

  while (!Close) {
    MainWindow.advance();

    Close = MainWindow.shouldClose();
  }
}

void Exrend2D::start() {
  Close = false;
  MainWindow.setShouldClose(false);
}

void Exrend2D::stop() {
  Close = true;
  MainWindow.setShouldClose(true);
}
