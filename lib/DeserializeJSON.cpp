#include "DeserializeJSON.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

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

void loadColor(const nlohmann::json &JSON, float (&Color)[4]) {
  // 0
  if (!JSON[0].is_number_float()) {
    std::cout
        << "[loadColor] WARNING: JSON[0] is not a float! Defaulting to 0.0f"
        << std::endl;
    Color[0] = 0.0f;
  } else {
    Color[0] = float(JSON[0]);
  }

  // 1
  if (!JSON[1].is_number_float()) {
    std::cout
        << "[loadColor] WARNING: JSON[1] is not a float! Defaulting to 0.0f"
        << std::endl;
    Color[1] = 0.0f;
  } else {
    Color[1] = float(JSON[1]);
  }

  // 2
  if (!JSON[2].is_number_float()) {
    std::cout
        << "[loadColor] WARNING: JSON[2] is not a float! Defaulting to 0.0f"
        << std::endl;
    Color[2] = 0.0f;
  } else {
    Color[2] = float(JSON[2]);
  }

  // 3
  if (!JSON[3].is_number_float()) {
    std::cout
        << "[loadColor] WARNING: JSON[3] is not a float! Defaulting to 0.0f"
        << std::endl;
    Color[3] = 0.0f;
  } else {
    Color[3] = float(JSON[3]);
  }
}

void loadPosition(const nlohmann::json &JSON, float (&Position)[3]) {
  // 0
  if (!JSON[0].is_number_float()) {
    std::cout << "[loadPosition()] WARNING: JSON[0] is not a float! Defaulting "
                 "to 0.0f"
              << std::endl;
    Position[0] = 0.0f;
  } else {
    Position[0] = float(JSON[0]);
  }

  // 1
  if (!JSON[1].is_number_float()) {
    std::cout << "[loadPosition()] WARNING: JSON[1] is not a float! Defaulting "
                 "to 0.0f"
              << std::endl;
    Position[1] = 0.0f;
  } else {
    Position[1] = float(JSON[1]);
  }

  // 2
  if (!JSON[2].is_number_float()) {
    std::cout << "[loadPosition()] WARNING: JSON[2] is not a float! Defaulting "
                 "to 0.0f"
              << std::endl;
    Position[2] = 0.0f;
  } else {
    Position[2] = float(JSON[2]);
  }
}

void loadTexCoords(const nlohmann::json &JSON, float (&TexCoords)[3]) {
  // 0
  if (!JSON[0].is_number_float()) {
    std::cout
        << "[loadTexCoords()] WARNING: JSON[0] is not a float! Defaulting "
           "to 0.0f"
        << std::endl;
    TexCoords[0] = 0.0f;
  } else {
    TexCoords[0] = float(JSON[0]);
  }

  // 1
  if (!JSON[1].is_number_float()) {
    std::cout
        << "[loadTexCoords()] WARNING: JSON[1] is not a float! Defaulting "
           "to 0.0f"
        << std::endl;
    TexCoords[1] = 0.0f;
  } else {
    TexCoords[1] = float(JSON[1]);
  }

  // 2
  if (!JSON[2].is_number_float()) {
    std::cout
        << "[loadTexCoords()] WARNING: JSON[2] is not a float! Defaulting "
           "to 0.0f"
        << std::endl;
    TexCoords[2] = 0.0f;
  } else {
    TexCoords[2] = float(JSON[2]);
  }
}

void loadQuadButtons(const nlohmann::json &JSON, Renderer &App) {
  int Counter = 0;
  for (const auto &QuadButton : JSON["QuadButtons"]) {
    std::cout << "QuadButton " << Counter << ": " << QuadButton << std::endl;
    Counter++;
    Quad CurrentQuad = Quad();

    loadColor(JSON["A"]["Color"], CurrentQuad.A.Color);
    loadPosition(JSON["A"]["Position"], CurrentQuad.A.Position);
    loadTexCoords(JSON["A"]["TexCoords"], CurrentQuad.A.TexCoords);

    loadColor(JSON["B"]["Color"], CurrentQuad.B.Color);
    loadPosition(JSON["B"]["Position"], CurrentQuad.B.Position);
    loadTexCoords(JSON["B"]["TexCoords"], CurrentQuad.B.TexCoords);

    loadColor(JSON["C"]["Color"], CurrentQuad.C.Color);
    loadPosition(JSON["C"]["Position"], CurrentQuad.C.Position);
    loadTexCoords(JSON["C"]["TexCoords"], CurrentQuad.C.TexCoords);

    loadColor(JSON["D"]["Color"], CurrentQuad.D.Color);
    loadPosition(JSON["D"]["Position"], CurrentQuad.D.Position);
    loadTexCoords(JSON["D"]["TexCoords"], CurrentQuad.D.TexCoords);

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
