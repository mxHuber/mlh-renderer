#ifndef MLH_RENDERER_QUAD_UTILS_HPP
#define MLH_RENDERER_QUAD_UTILS_HPP

#include "Quad.hpp"

namespace mlh {

static inline void changeQuadTexture(Quad &QuadToEdit, float TextureID) {
  QuadToEdit.A.TexCoords[2] = TextureID;
  QuadToEdit.B.TexCoords[2] = TextureID;
  QuadToEdit.C.TexCoords[2] = TextureID;
  QuadToEdit.D.TexCoords[2] = TextureID;
}

} // namespace mlh

#endif
