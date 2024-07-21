#ifndef EXREND2D_QUAD_GENERATOR_HPP
#define EXREND2D_QUAD_GENERATOR_HPP

#include "Quad.hpp"

class QuadGenerator {
public:
  static Quad getQuad() { return BasicQuad; }

private:
  static Vertex A;
  static Vertex B;
  static Vertex C;
  static Vertex D;
  static Quad BasicQuad;
};

#endif
