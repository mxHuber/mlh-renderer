#ifndef MLH_RENDERER_QUAD_GENERATOR_HPP
#define MLH_RENDERER_QUAD_GENERATOR_HPP

#include "Quad.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace mlh {

class QuadGenerator {
public:
  static Quad getBasicQuad() { return BasicQuad; }
  static void printBasicQuadValues() {
    std::cout << "Basic Quad:" << std::endl;
    std::cout << "A:" << std::endl;
    std::cout << "- Pos: (" << BasicQuad.A.Position[0] << ", "
              << BasicQuad.A.Position[1] << ", " << BasicQuad.A.Position[2]
              << ")" << std::endl;
    std::cout << "- Col: (" << BasicQuad.A.Color[0] << ", "
              << BasicQuad.A.Color[1] << ", " << BasicQuad.A.Color[2] << ", "
              << BasicQuad.A.Color[3] << ")" << std::endl;
    std::cout << "- Tex: (" << BasicQuad.A.TexCoords[0] << ", "
              << BasicQuad.A.TexCoords[1] << ", " << BasicQuad.A.TexCoords[2]
              << ")" << std::endl;
    std::cout << "B:" << std::endl;
    std::cout << "- Pos: (" << BasicQuad.B.Position[0] << ", "
              << BasicQuad.B.Position[1] << ", " << BasicQuad.B.Position[2]
              << ")" << std::endl;
    std::cout << "- Col: (" << BasicQuad.B.Color[0] << ", "
              << BasicQuad.B.Color[1] << ", " << BasicQuad.B.Color[2] << ", "
              << BasicQuad.B.Color[3] << ")" << std::endl;
    std::cout << "- Tex: (" << BasicQuad.B.TexCoords[0] << ", "
              << BasicQuad.B.TexCoords[1] << ", " << BasicQuad.B.TexCoords[2]
              << ")" << std::endl;
    std::cout << "C:" << std::endl;
    std::cout << "- Pos: (" << BasicQuad.C.Position[0] << ", "
              << BasicQuad.C.Position[1] << ", " << BasicQuad.C.Position[2]
              << ")" << std::endl;
    std::cout << "- Col: (" << BasicQuad.C.Color[0] << ", "
              << BasicQuad.C.Color[1] << ", " << BasicQuad.C.Color[2] << ", "
              << BasicQuad.C.Color[3] << ")" << std::endl;
    std::cout << "- Tex: (" << BasicQuad.C.TexCoords[0] << ", "
              << BasicQuad.C.TexCoords[1] << ", " << BasicQuad.C.TexCoords[2]
              << ")" << std::endl;
    std::cout << "D:" << std::endl;
    std::cout << "- Pos: (" << BasicQuad.D.Position[0] << ", "
              << BasicQuad.D.Position[1] << ", " << BasicQuad.D.Position[2]
              << ")" << std::endl;
    std::cout << "- Col: (" << BasicQuad.D.Color[0] << ", "
              << BasicQuad.D.Color[1] << ", " << BasicQuad.D.Color[2] << ", "
              << BasicQuad.D.Color[3] << ")" << std::endl;
    std::cout << "- Tex: (" << BasicQuad.D.TexCoords[0] << ", "
              << BasicQuad.D.TexCoords[1] << ", " << BasicQuad.D.TexCoords[2]
              << ")" << std::endl;
  }
  static Quad getRandomQuad() {
    srand(static_cast<unsigned>(time(0)));

    float RandFloatAX = static_cast<float>(rand()) / ((float)RAND_MAX / 1.0f);
    float RandFloatAY = static_cast<float>(rand()) / ((float)RAND_MAX / 1.0f);
    float RandFloatBX = static_cast<float>(rand()) / ((float)RAND_MAX / 1.0f);
    float RandFloatBY = static_cast<float>(rand()) / ((float)RAND_MAX / 1.0f);
    float RandFloatCX = static_cast<float>(rand()) / ((float)RAND_MAX / 1.0f);
    float RandFloatCY = static_cast<float>(rand()) / ((float)RAND_MAX / 1.0f);
    float RandFloatDX = static_cast<float>(rand()) / ((float)RAND_MAX / 1.0f);
    float RandFloatDY = static_cast<float>(rand()) / ((float)RAND_MAX / 1.0f);

    std::cout << "RandFloatAX: " << RandFloatAX << std::endl;
    std::cout << "RandFloatAY: " << RandFloatAY << std::endl;
    std::cout << "RandFloatBX: " << RandFloatBX << std::endl;
    std::cout << "RandFloatBY: " << RandFloatBY << std::endl;
    std::cout << "RandFloatCX: " << RandFloatCX << std::endl;
    std::cout << "RandFloatCY: " << RandFloatCY << std::endl;
    std::cout << "RandFloatDX: " << RandFloatDX << std::endl;
    std::cout << "RandFloatDY: " << RandFloatDY << std::endl;

    Quad ReturnQuad = getBasicQuad();
    ReturnQuad.A.Position[0] = RandFloatAX;
    ReturnQuad.A.Position[1] = RandFloatAY;
    ReturnQuad.B.Position[0] = RandFloatBX;
    ReturnQuad.B.Position[1] = RandFloatBY;
    ReturnQuad.C.Position[0] = RandFloatCX;
    ReturnQuad.C.Position[1] = RandFloatCY;
    ReturnQuad.D.Position[0] = RandFloatDX;
    ReturnQuad.D.Position[1] = RandFloatDY;

    ReturnQuad.A.Position[2] = -0.1f;
    ReturnQuad.B.Position[2] = -0.1f;
    ReturnQuad.C.Position[2] = -0.1f;
    ReturnQuad.D.Position[2] = -0.1f;

    ReturnQuad.A.Color[0] = RandFloatAX;
    ReturnQuad.A.Color[1] = RandFloatAY;
    ReturnQuad.A.Color[2] = (RandFloatAX + RandFloatAY) / 2.0f;

    ReturnQuad.B.Color[0] = RandFloatBX;
    ReturnQuad.B.Color[1] = RandFloatBY;
    ReturnQuad.B.Color[2] = (RandFloatBX + RandFloatBY) / 2.0f;

    ReturnQuad.C.Color[0] = RandFloatCX;
    ReturnQuad.C.Color[1] = RandFloatCY;
    ReturnQuad.C.Color[2] = (RandFloatCX + RandFloatCY) / 2.0f;

    ReturnQuad.D.Color[0] = RandFloatDX;
    ReturnQuad.D.Color[1] = RandFloatDY;
    ReturnQuad.D.Color[2] = (RandFloatDX + RandFloatDY) / 2.0f;

    return ReturnQuad;
  }

private:
  inline static Vertex A = {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                            1.0f,  1.0f,  0.0f, 0.0f, 0.0f};
  inline static Vertex B = {0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
                            1.0f, 1.0f,  1.0f, 0.0f, 0.0f};
  inline static Vertex C = {0.5f, 0.5f, 0.0f, 0.0f, 0.5f,
                            0.5f, 1.0f, 1.0f, 1.0f, 0.0f};
  inline static Vertex D = {-0.5f, 0.5f, 0.0f, 0.0f, 0.8f,
                            0.2f,  1.0f, 0.0f, 1.0f, 0.0f};
  inline static Quad BasicQuad = {A, B, C, D};
};

} // namespace mlh

#endif
