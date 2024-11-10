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
  static Vertex A;
  static Vertex B;
  static Vertex C;
  static Vertex D;
  static Quad BasicQuad;
};

} // namespace mlh

#endif
