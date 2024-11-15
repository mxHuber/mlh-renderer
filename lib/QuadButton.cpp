#include "QuadButton.hpp"
#include <algorithm>

namespace mlh {

QuadButton::QuadButton(const Quad &ClickableArea, unsigned int &WindowWidth,
                       unsigned int &WindowHeight)
    : WindowWidth(WindowWidth), WindowHeight(WindowHeight),
      ClickableArea(ClickableArea) {

  // TODO: sort positions, so that A, B, C and D always correspond to bottom
  // left, bottom right, top right and top left.

  LeftBoundary =
      std::min(ClickableArea.A.Position[0], ClickableArea.D.Position[0]) +
      ClickableArea.A.Position[0] / WindowWidth;
  RightBoundary =
      std::max(ClickableArea.B.Position[0], ClickableArea.C.Position[0]) +
      ClickableArea.B.Position[0] / WindowWidth;
  TopBoundary =
      std::min(ClickableArea.C.Position[1], ClickableArea.D.Position[1]) +
      ClickableArea.C.Position[1] / WindowWidth;
  BottomBoundary =
      std::max(ClickableArea.A.Position[1], ClickableArea.B.Position[1]) +
      ClickableArea.D.Position[1] / WindowWidth;
}

const bool QuadButton::checkBounds(float XPos, float YPos) const {
  return XPos > LeftBoundary && XPos < RightBoundary && YPos > BottomBoundary &&
         YPos < TopBoundary;
}

} // namespace mlh
