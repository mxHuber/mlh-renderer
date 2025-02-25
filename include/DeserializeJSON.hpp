#ifndef MLH_RENDERER_DESERIALIZE_JSON_HPP
#define MLH_RENDERER_DESERIALIZE_JSON_HPP

#include "Renderer.hpp"
#include <nlohmann/json.hpp>

namespace mlh {

class DeserializeJSON {
public:
  static void deserializeJSON(const std::string &Path, Renderer &App);

private:
  static void loadColor(nlohmann::json JSON, float (&Color)[4]);
  static void loadPosition(const nlohmann::json &JSON, float (&Position)[3]);
  static void loadTexCoords(const nlohmann::json &JSON, float (&TexCoords)[3]);
  static void loadQuadButtons(const nlohmann::json &JSON, Renderer &App);
};

} // namespace mlh

#endif
