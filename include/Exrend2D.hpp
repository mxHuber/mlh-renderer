#ifndef EXREND2D_EXREND2D_HPP
#define EXREND2D_EXREND2D_HPP

#include "RectangleRenderer.hpp"
#include "Window.hpp"

class Exrend2D {
public:
  Exrend2D();
  ~Exrend2D();

  void runLoop();
  void stop();
  void start();

private:
  Window MainWindow = Window(800, 600, "Exrend2D");
  RectangleRenderer Renderer;
  bool Close = false;
};

#endif
