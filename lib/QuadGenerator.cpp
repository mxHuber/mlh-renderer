#include "QuadGenerator.hpp"

namespace mlh {

Vertex QuadGenerator::A = {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                           1.0f,  1.0f,  0.0f, 0.0f, 0.0f};
Vertex QuadGenerator::B = {0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
                           1.0f, 1.0f,  0.0f, 0.0f, 0.0f};
Vertex QuadGenerator::C = {0.5f, 0.5f, 0.0f, 0.0f, 0.5f,
                           0.5f, 1.0f, 0.0f, 0.0f, 0.0f};
Vertex QuadGenerator::D = {-0.5f, 0.5f, 0.0f, 0.0f, 0.8f,
                           0.2f,  1.0f, 0.0f, 0.0f, 0.0f};
Quad QuadGenerator::BasicQuad = {A, B, C, D};

} // namespace mlh
