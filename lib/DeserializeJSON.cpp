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

void DeserializeJSON::checkIfQuadJSONIsValid(const nlohmann::json &QuadJSON) {
  assert(QuadJSON.contains("A"));
  assert(QuadJSON.contains("B"));
  assert(QuadJSON.contains("C"));
  assert(QuadJSON.contains("D"));

  assert(QuadJSON["A"].contains("Color"));
  assert(QuadJSON["A"].contains("Position"));
  assert(QuadJSON["A"].contains("TexCoords"));

  assert(QuadJSON["B"].contains("Color"));
  assert(QuadJSON["B"].contains("Position"));
  assert(QuadJSON["B"].contains("TexCoords"));

  assert(QuadJSON["C"].contains("Color"));
  assert(QuadJSON["C"].contains("Position"));
  assert(QuadJSON["C"].contains("TexCoords"));

  assert(QuadJSON["D"].contains("Color"));
  assert(QuadJSON["D"].contains("Position"));
  assert(QuadJSON["D"].contains("TexCoords"));
}

Quad DeserializeJSON::loadQuad(const nlohmann::json &QuadJSON) {
  Quad NewQuad = Quad();

  checkIfQuadJSONIsValid(QuadJSON);

  loadColor(QuadJSON["A"]["Color"], NewQuad.A.Color);
  loadPosition(QuadJSON["A"]["Position"], NewQuad.A.Position);
  loadTexCoords(QuadJSON["A"]["TexCoords"], NewQuad.A.TexCoords);

  loadColor(QuadJSON["B"]["Color"], NewQuad.B.Color);
  loadPosition(QuadJSON["B"]["Position"], NewQuad.B.Position);
  loadTexCoords(QuadJSON["B"]["TexCoords"], NewQuad.B.TexCoords);

  loadColor(QuadJSON["C"]["Color"], NewQuad.C.Color);
  loadPosition(QuadJSON["C"]["Position"], NewQuad.C.Position);
  loadTexCoords(QuadJSON["C"]["TexCoords"], NewQuad.C.TexCoords);

  loadColor(QuadJSON["D"]["Color"], NewQuad.D.Color);
  loadPosition(QuadJSON["D"]["Position"], NewQuad.D.Position);
  loadTexCoords(QuadJSON["D"]["TexCoords"], NewQuad.D.TexCoords);

  return std::move(NewQuad);
}

void DeserializeJSON::loadQuads(const nlohmann::json &JSON, Renderer &App) {
  if (!JSON.contains("Quads")) {
    return;
  }

  for (const auto &QuadJSON : JSON["Quads"]) {
    Quad CurrentQuad = loadQuad(QuadJSON);
    App.addQuad(CurrentQuad);
  }
}

void DeserializeJSON::loadQuadButtons(const nlohmann::json &JSON,
                                      Renderer &App) {
  if (!JSON.contains("QuadButtons")) {
    return;
  }

  for (const auto &QuadButtonJSON : JSON["QuadButtons"]) {
    Quad CurrentQuad = loadQuad(QuadButtonJSON);
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
  loadQuads(JSON, App);
  loadQuadButtons(JSON, App);
}

} // namespace mlh
