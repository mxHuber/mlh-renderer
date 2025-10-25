#include "PrintQuads.hpp"
#include <iostream>

namespace mlh {

void printVertex(const Vertex &VertexToPrint) {
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

void printQuad(const Quad &QuadToPrint) {
  std::cout << "Vertex A" << std::endl;
  printVertex(QuadToPrint.A);
  std::cout << "Vertex B" << std::endl;
  printVertex(QuadToPrint.B);
  std::cout << "Vertex C" << std::endl;
  printVertex(QuadToPrint.C);
  std::cout << "Vertex D" << std::endl;
  printVertex(QuadToPrint.D);
}

void printQuads(const std::vector<Quad> &QuadToPrint) {
  for (const Quad Curr : QuadToPrint) {
    printQuad(Curr);
  }
}

} // namespace mlh
