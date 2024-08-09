#include "QuadButton.hpp"
#include <iostream>

QuadButton::QuadButton(const Quad &ClickableArea, int &WindowWidth,
                       int &WindowHeight)
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

  std::cout << "A: " << ClickableArea.A.Position[0] << ", "
            << ClickableArea.A.Position[1] << std::endl;
  std::cout << "B: " << ClickableArea.B.Position[0] << ", "
            << ClickableArea.B.Position[1] << std::endl;
  std::cout << " C: " << ClickableArea.C.Position[0] << ", "
            << ClickableArea.C.Position[1] << std::endl;
  std::cout << " D: " << ClickableArea.D.Position[0] << ", "
            << ClickableArea.D.Position[1] << std::endl;

  std::cout << "Top: " << TopBoundary << "\n"
            << "Bottom: " << BottomBoundary << "\n"
            << "Left: " << LeftBoundary << "\n"
            << "Right: " << RightBoundary << "\n"
            << std::endl;
}

const bool QuadButton::checkClick(float XPos, float YPos) const {
  if (XPos > LeftBoundary && XPos < RightBoundary && YPos > BottomBoundary &&
      YPos < TopBoundary) {
    std::cout << "XPos: " << XPos << "\n"
              << "YPos: " << YPos << "\n"
              << std::endl;
  }
  return XPos > LeftBoundary && XPos < RightBoundary && YPos > BottomBoundary &&
         YPos < TopBoundary;
}
