#ifndef MLH_RENDERER_PRINT_QUADS_HPP
#define MLH_RENDERER_PRINT_QUADS_HPP

#include "Quad.hpp"
#include <vector>

namespace mlh {

void printVertex(const Vertex &VertexToPrint);
void printQuad(const Quad &QuadToPrint);
void printQuads(const std::vector<Quad> &QuadToPrint);

} // namespace mlh

#endif
