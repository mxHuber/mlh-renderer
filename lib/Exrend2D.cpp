#include "Exrend2D.hpp"
#include <iostream>

Exrend2D::Exrend2D() {}

Exrend2D::~Exrend2D() { glfwTerminate(); }

void Exrend2D::runLoop() {
  start();

  int Counter = 0;
  int Threshold = 300;

  while (!Close) {
    if (Counter > Threshold) {

      std::cout << Threshold << " while loop cycles have passed" << std::endl;
      Threshold += 300;
    }
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
