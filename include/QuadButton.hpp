#ifndef MLH_RENDERER_QUAD_BUTTON_HPP
#define MLH_RENDERER_QUAD_BUTTON_HPP

#include "Quad.hpp"
#include <functional>
#include <iostream>

namespace mlh {

class QuadButton {
public:
  QuadButton(const Quad &ClickableArea, int &WindowWidth, int &WindowHeight)
      : WindowWidth(WindowWidth), WindowHeight(WindowHeight),
        ClickableArea(ClickableArea), ButtonID(ButtonIDCounter++) {

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

  const bool checkBounds(float XPos, float YPos) const {
    return XPos > LeftBoundary && XPos < RightBoundary &&
           YPos > BottomBoundary && YPos < TopBoundary;
  }

  inline const Quad &getQuad() const { return ClickableArea; }

  void onPress() { Func(); }
  void setFunc(std::function<void()> NewFunc) { Func = NewFunc; }

private:
  Quad ClickableArea;

  float TopBoundary = 0.0f;
  float BottomBoundary = 0.0f;
  float LeftBoundary = 0.0f;
  float RightBoundary = 0.0f;

  int &WindowWidth;
  int &WindowHeight;

  inline static int ButtonIDCounter = 0;
  int ButtonID = -1;

  std::function<void()> Func = [ButtonID = ButtonID]() {
    std::cout << "Button with ID " << ButtonID << " was pressed!" << std::endl;
  };
};

} // namespace mlh

#endif
