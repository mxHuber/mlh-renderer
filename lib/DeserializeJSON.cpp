#include "DeserializeJSON.hpp"
#include "Quad.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

namespace mlh {

void loadBackground(const nlohmann::json &JSON, Renderer &App) {
  if (!JSON.contains("BackgroundImage")) {
    return;
  }

  if (!JSON["BackgroundImage"].is_string()) {
    return;
  }

  std::string BackgroundImagePath = JSON["BackgroundImage"];
  float BackgroundImageID = App.createTexture(BackgroundImagePath);
  App.setBackground(BackgroundImageID);
}

void DeserializeJSON::loadColor(nlohmann::json JSON, float (&Color)[4]) {
  // 0
  if (!JSON[0].is_number()) {
    std::cout
        << "[loadColor] WARNING: JSON[0] is not a float! Defaulting to 0.0f"
        << std::endl;
    Color[0] = 0.0f;
  } else {
    Color[0] = JSON[0];
  }

  // 1
  if (!JSON[1].is_number()) {
    std::cout
        << "[loadColor] WARNING: JSON[1] is not a float! Defaulting to 0.0f"
        << std::endl;
    Color[1] = 0.0f;
  } else {
    Color[1] = JSON[1];
  }

  // 2
  if (!JSON[2].is_number()) {
    std::cout
        << "[loadColor] WARNING: JSON[2] is not a float! Defaulting to 0.0f"
        << "JSON[2]: " << JSON[2] << std::endl;
    Color[2] = 0.0f;
  } else {
    Color[2] = JSON[2];
  }

  // 3
  if (!JSON[3].is_number()) {
    std::cout
        << "[loadColor] WARNING: JSON[3] is not a float! Defaulting to 0.0f"
        << "JSON[3]: " << JSON[3] << std::endl;
    Color[3] = 0.0f;
  } else {
    Color[3] = JSON[3];
  }
}

void DeserializeJSON::loadPosition(const nlohmann::json &JSON,
                                   float (&Position)[3]) {
  // 0
  if (!JSON[0].is_number()) {
    std::cout << "[loadPosition()] WARNING: JSON[0] is not a float! Defaulting "
                 "to 0.0f"
              << std::endl;
    Position[0] = 0.0f;
  } else {
    Position[0] = JSON[0];
  }

  // 1
  if (!JSON[1].is_number()) {
    std::cout << "[loadPosition()] WARNING: JSON[1] is not a float! Defaulting "
                 "to 0.0f"
              << std::endl;
    Position[1] = 0.0f;
  } else {
    Position[1] = JSON[1];
  }

  // 2
  if (!JSON[2].is_number()) {
    std::cout << "[loadPosition()] WARNING: JSON[2] is not a float! Defaulting "
                 "to 0.0f"
              << std::endl;
    Position[2] = 0.0f;
  } else {
    Position[2] = JSON[2];
  }
}

void DeserializeJSON::loadTexCoords(const nlohmann::json &JSON,
                                    float (&TexCoords)[3]) {
  // 0
  if (!JSON[0].is_number()) {
    std::cout
        << "[loadTexCoords()] WARNING: JSON[0] is not a float! Defaulting "
           "to 0.0f"
        << std::endl;
    TexCoords[0] = 0.0f;
  } else {
    TexCoords[0] = JSON[0];
  }

  // 1
  if (!JSON[1].is_number()) {
    std::cout
        << "[loadTexCoords()] WARNING: JSON[1] is not a float! Defaulting "
           "to 0.0f"
        << std::endl;
    TexCoords[1] = 0.0f;
  } else {
    TexCoords[1] = JSON[1];
  }

  // 2
  if (!JSON[2].is_number()) {
    std::cout
        << "[loadTexCoords()] WARNING: JSON[2] is not a float! Defaulting "
           "to 0.0f"
        << "\nJSON[2]: " << JSON[2] << std::endl;
    TexCoords[2] = 0.0f;
  } else {
    TexCoords[2] = JSON[2];
  }
}

void DeserializeJSON::loadQuadButtons(const nlohmann::json &JSON,
                                      Renderer &App) {
  for (const auto &QuadButton : JSON["QuadButtons"]) {
    Quad CurrentQuad = Quad();

    loadColor(QuadButton["A"]["Color"], CurrentQuad.A.Color);
    loadPosition(QuadButton["A"]["Position"], CurrentQuad.A.Position);
    loadTexCoords(QuadButton["A"]["TexCoords"], CurrentQuad.A.TexCoords);

    loadColor(QuadButton["B"]["Color"], CurrentQuad.B.Color);
    loadPosition(QuadButton["B"]["Position"], CurrentQuad.B.Position);
    loadTexCoords(QuadButton["B"]["TexCoords"], CurrentQuad.B.TexCoords);

    loadColor(QuadButton["C"]["Color"], CurrentQuad.C.Color);
    loadPosition(QuadButton["C"]["Position"], CurrentQuad.C.Position);
    loadTexCoords(QuadButton["C"]["TexCoords"], CurrentQuad.C.TexCoords);

    loadColor(QuadButton["D"]["Color"], CurrentQuad.D.Color);
    loadPosition(QuadButton["D"]["Position"], CurrentQuad.D.Position);
    loadTexCoords(QuadButton["D"]["TexCoords"], CurrentQuad.D.TexCoords);

    App.createQuadButton(CurrentQuad);
  }
}

void DeserializeJSON::deserializeJSON(const std::string &Path, Renderer &App) {
  std::ifstream Stream(Path);
  if (!Stream.is_open()) {
    std::cout << "File could not be opened. Is the file path correct?"
              << std::endl;
    return;
  }

  nlohmann::json JSON = nlohmann::json::parse(Stream);
  if (JSON.is_discarded()) {
    std::cout << "JSON was discarded." << std::endl;
    return;
  }

  loadBackground(JSON, App);
  loadQuadButtons(JSON, App);
}

} // namespace mlh
