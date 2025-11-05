#ifndef MLH_RENDERER_CLICKABLE_AREA_HPP
#define MLH_RENDERER_CLICKABLE_AREA_HPP

#include "RectangleBoundary.hpp"

namespace mlh {

class ClickableArea {
public:
  ClickableArea(RectangleBoundary Boundary) : Boundary(Boundary) {};

  const bool checkBounds(const float XPos, const float YPos) const {
    return XPos > Boundary.LeftBoundary && XPos < Boundary.RightBoundary &&
           YPos > Boundary.BottomBoundary && YPos < Boundary.TopBoundary;
  }

private:
  RectangleBoundary Boundary;
};

} // namespace mlh

#endif
