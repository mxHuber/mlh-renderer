#ifndef MLH_RENDERER_QUAD_BUTTON_HPP
#define MLH_RENDERER_QUAD_BUTTON_HPP

#include "Quad.hpp"
#include "RectangleBoundary.hpp"
#include "SettingsData.hpp"
#include <functional>
#include <iostream>

namespace mlh {

class QuadButton {
public:
  QuadButton(const Quad &QuadOfButton)
      : QuadOfButton(QuadOfButton),
        ClickableArea(getBoundaryOfQuad(QuadOfButton, Settings)),
        ButtonID(ButtonIDCounter++) {}

  inline const bool isPosInBoundary(float XPos, float YPos) const {
    return isPointInBoundary(XPos, YPos, ClickableArea);
  }

  inline const Quad getQuad() const { return QuadOfButton; }

  inline const RectangleBoundary &getClickableArea() const {
    return ClickableArea;
  }

  inline const void setClickableArea(RectangleBoundary newClickableArea) {
    ClickableArea = newClickableArea;
  }

  inline virtual void checkPress(float XPos, float YPos) {
    if (isPosInBoundary(XPos, YPos)) {
      onPress();
    }
  }

  inline virtual void onPress() { Func(); }
  inline void setFunc(std::function<void()> NewFunc) { Func = NewFunc; }

protected:
  Quad QuadOfButton;
  RectangleBoundary ClickableArea;
  SettingsData Settings = SettingsData();

  float TopBoundary = 0.0f;
  float BottomBoundary = 0.0f;
  float LeftBoundary = 0.0f;
  float RightBoundary = 0.0f;

  inline static int ButtonIDCounter = 0;
  int ButtonID = -1;

  std::function<void()> Func = [ButtonID = ButtonID]() {
    std::cout << "Button with ID " << ButtonID << " was pressed!" << std::endl;
  };
};

} // namespace mlh

#endif
