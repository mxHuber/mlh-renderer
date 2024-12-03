#ifndef MLH_RENDERER_DESERIALIZE_JSON_HPP
#define MLH_RENDERER_DESERIALIZE_JSON_HPP

#include "Renderer.hpp"

namespace mlh {
class DeserializeJSON {
public:
  void deserializeJSON(const std::string &Path, Renderer &App);
};
} // namespace mlh

#endif
