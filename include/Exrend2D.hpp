#ifndef EXREND2D_EXREND2D_HPP
#define EXREND2D_EXREND2D_HPP

#include "Window.hpp"

class Exrend2D {
public:
  Exrend2D();
  ~Exrend2D();

  void runLoop();
  void stop();
  void start();

  void addQuad(const Quad &ToAdd) { MainWindow.addQuad(ToAdd); }

private:
  Window MainWindow = Window(800, 600, "Exrend2D");
  bool Close = false;
};

#endif
