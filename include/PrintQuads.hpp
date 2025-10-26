#ifndef MLH_RENDERER_PRINT_QUADS_HPP
#define MLH_RENDERER_PRINT_QUADS_HPP

#include "Quad.hpp"
#include <iostream>
#include <vector>

namespace mlh {

static void printVertex(const Vertex &VertexToPrint) {
  std::cout << " - Position:  " << VertexToPrint.Position[0] << ", "
            << VertexToPrint.Position[1] << ", " << VertexToPrint.Position[2]
            << std::endl;
  std::cout << " - Color:     " << VertexToPrint.Color[0] << ", "
            << VertexToPrint.Color[1] << ", " << VertexToPrint.Color[2] << ", "
            << VertexToPrint.Color[3] << std::endl;
  std::cout << " - TexCoords: " << VertexToPrint.TexCoords[0] << ", "
            << VertexToPrint.TexCoords[1] << ", " << VertexToPrint.TexCoords[2]
            << std::endl;
}

static void printQuad(const Quad &QuadToPrint) {
  std::cout << "Vertex A" << std::endl;
  printVertex(QuadToPrint.A);
  std::cout << "Vertex B" << std::endl;
  printVertex(QuadToPrint.B);
  std::cout << "Vertex C" << std::endl;
  printVertex(QuadToPrint.C);
  std::cout << "Vertex D" << std::endl;
  printVertex(QuadToPrint.D);
}

static void printQuads(const std::vector<Quad> &QuadToPrint) {
  for (const Quad Curr : QuadToPrint) {
    printQuad(Curr);
  }
}

} // namespace mlh

#endif
