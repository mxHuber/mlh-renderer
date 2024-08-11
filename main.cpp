#include "Exrend2D.hpp"
#include "QuadGenerator.hpp"
#include <iostream>

// settings
const unsigned int WindowWidth = 800;
const unsigned int WindowHeight = 600;

int main() {
  // TODO: third value in position is currently not used.
  // Find out if it can be used for layering, aka determine what should render
  // infront, if there are overlapping sprites

  // TODO: add namespaces. For example 'exr' or 'er2'

  std::cout << "Creating Exrend2D obj" << std::endl;
  Exrend2D App = Exrend2D();

  std::cout << "Adding Quad" << std::endl;
  App.addQuad(QuadGenerator::getQuad());

  std::cout << "Run loop" << std::endl;
  App.runLoop();

  return 0;
}
