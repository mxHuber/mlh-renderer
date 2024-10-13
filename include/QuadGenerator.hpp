#ifndef MLH_RENDERER_QUAD_GENERATOR_HPP
#define MLH_RENDERER_QUAD_GENERATOR_HPP

#include "Quad.hpp"

namespace mlh {

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

} // namespace mlh

#endif
