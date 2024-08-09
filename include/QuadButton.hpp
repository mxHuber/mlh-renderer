#ifndef EXREND2D_QUAD_BUTTON_HPP
#define EXREND2D_QUAD_BUTTON_HPP

#include "Quad.hpp"

class QuadButton {
public:
  QuadButton(const Quad &ClickableArea, int &WindowWidth, int &WindowHeight);

  const bool checkClick(float XPos, float YPos) const;

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

#endif
