#ifndef MLH_RENDERER_CHECKBOX_BUTTON_HPP
#define MLH_RENDERER_CHECKBOX_BUTTON_HPP

#include "QuadButton.hpp"
#include "RectangleBoundary.hpp"

namespace mlh {

class CheckboxButton : public QuadButton {
public:
  // Unchecked and checked quads normally only differ in their tex coords, but
  // could also differ in their size or color.
  CheckboxButton(const Quad &UncheckedQuad, const Quad &CheckedQuad)
      : QuadButton(UncheckedQuad), UncheckedQuad(UncheckedQuad),
        CheckedQuad(CheckedQuad),
        UncheckedBoundary(getBoundaryOfQuad(UncheckedQuad, Settings)),
        CheckedBoundary(getBoundaryOfQuad(CheckedQuad, Settings)) {};

  inline void checkPress(float XPos, float YPos) override {
    if (isPosInBoundary(XPos, YPos)) {
      onPress();
    }
  }

  inline void onPress() override {
    // If a function is set, run it
    Func();
    // Flip check bool
    isChecked = !isChecked;
    // Set the appropriate Quad. This will usually lead to a different texture
    // for example.
    QuadOfButton = isChecked ? CheckedQuad : UncheckedQuad;
    // Set the corresponding boundary of the quad
    isChecked ? setClickableArea(CheckedBoundary)
              : setClickableArea(UncheckedBoundary);
  }

protected:
  bool isChecked = false;
  const Quad UncheckedQuad;
  const Quad CheckedQuad;
  const RectangleBoundary UncheckedBoundary;
  const RectangleBoundary CheckedBoundary;
};

} // namespace mlh

#endif
