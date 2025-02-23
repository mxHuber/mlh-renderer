#ifndef MLH_RENDERER_QUAD_BUTTON_HPP
#define MLH_RENDERER_QUAD_BUTTON_HPP

#include "Quad.hpp"

namespace mlh {

class QuadButton {
public:
  QuadButton(const Quad &ClickableArea, int &WindowWidth, int &WindowHeight);

  const bool checkBounds(float XPos, float YPos) const;

  inline const Quad &getQuad() const { return ClickableArea; }

private:
  Quad ClickableArea;

  float TopBoundary = 0.0f;
  float BottomBoundary = 0.0f;
  float LeftBoundary = 0.0f;
  float RightBoundary = 0.0f;

  int &WindowWidth;
  int &WindowHeight;
};

} // namespace mlh

#endif
