#ifndef MLH_RENDERER_MENU_HPP
#define MLH_RENDERER_MENU_HPP

#include "CheckboxButton.hpp"
#include "QuadButton.hpp"

namespace mlh {

// TODO:
class Menu {
public:
  Menu(float Width, float Height) : Width(Width), Height(Height) {};

  std::vector<Quad> getQuads() const {
    std::vector<Quad> QuadsToReturn = {MenuBackground};

    for (const auto &Curr : QuadButtons) {
      QuadsToReturn.push_back(Curr.getQuad());
    }

    for (const auto &Curr : CheckboxButtons) {
      QuadsToReturn.push_back(Curr.getQuad());
    }

    return QuadsToReturn;
  }

  void checkPresses(float XPos, float YPos) {
    for (auto &Curr : QuadButtons) {
      Curr.checkPress(XPos, YPos);
    }

    for (auto &Curr : CheckboxButtons) {
      Curr.checkPress(XPos, YPos);
    }
  }

protected:
  float Width = 0.0f;
  float Height = 0.0f;
  Quad MenuBackground;
  std::vector<QuadButton> QuadButtons;
  std::vector<CheckboxButton> CheckboxButtons;
};

} // namespace mlh

#endif
