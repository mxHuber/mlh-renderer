#ifndef MLH_RENDERER_RECTANGLE_BOUNDARY_HPP
#define MLH_RENDERER_RECTANGLE_BOUNDARY_HPP

#include "Quad.hpp"
#include "SettingsData.hpp"
#include <algorithm>

namespace mlh {

struct RectangleBoundary {
  float TopBoundary = 0.0f;
  float BottomBoundary = 0.0f;
  float LeftBoundary = 0.0f;
  float RightBoundary = 0.0f;
};

static RectangleBoundary getBoundaryOfQuad(const Quad &CurrQuad,
                                           const SettingsData &Settings) {
  RectangleBoundary ToReturn;

  // TODO: sort positions, so that A, B, C and D always correspond to bottom
  // left, bottom right, top right and top left.

  ToReturn.LeftBoundary =
      std::min(CurrQuad.A.Position[0], CurrQuad.D.Position[0]) +
      CurrQuad.A.Position[0] / Settings.WindowWidth;
  ToReturn.RightBoundary =
      std::max(CurrQuad.B.Position[0], CurrQuad.C.Position[0]) +
      CurrQuad.B.Position[0] / Settings.WindowWidth;
  ToReturn.TopBoundary =
      std::min(CurrQuad.C.Position[1], CurrQuad.D.Position[1]) +
      CurrQuad.C.Position[1] / Settings.WindowWidth;
  ToReturn.BottomBoundary =
      std::max(CurrQuad.A.Position[1], CurrQuad.B.Position[1]) +
      CurrQuad.D.Position[1] / Settings.WindowWidth;

  return ToReturn;
}

static bool isPointInBoundary(const float XPos, const float YPos,
                              const RectangleBoundary &Boundary) {
  return XPos > Boundary.LeftBoundary && XPos < Boundary.RightBoundary &&
         YPos > Boundary.BottomBoundary && YPos < Boundary.TopBoundary;
}

} // namespace mlh

#endif
