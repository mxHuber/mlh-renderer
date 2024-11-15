#ifndef MLH_RENDERER_RECTANGLE_RENDERER_HPP
#define MLH_RENDERER_RECTANGLE_RENDERER_HPP

#include <array>

#include "Quad.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"

namespace mlh {

constexpr size_t MaxQuads = 8192;
constexpr size_t MaxVertices = MaxQuads * 4;
constexpr size_t MaxIndices = MaxQuads * 6;
constexpr size_t MaxTextures = 16;

class RectangleRenderer {
public:
  RectangleRenderer() = default;
  RectangleRenderer(int WindowWidth, int WindowHeight);

  float createTexture(const std::string &Path);

  void addToBatch(const Quad &ToAdd);
  void drawBatch();
  void resetData();

  void setShader(const std::string &Vertex, const std::string &Fragment);

private:
  Shader RecShader = Shader();

  std::array<unsigned int, MaxTextures> TextureSlots = {};
  unsigned int TextureSlotIndex = 1;
  // if we just want to render a color, we use the white texture
  unsigned int WhiteTexture = 0;
  unsigned int WhiteTextureSlot = 0;

  unsigned int VAO, VBO, EBO;
  Vertex Vertices[MaxVertices] = {};
  unsigned int VerticesIndex = 0, IndicesCounter = 0;
  int WindowWidth = 800;
  int WindowHeight = 600;

  bool isInitialized = false;

  void checkForOpenGLErrors(const std::string &AdditionalInfo = "");
  void init();
  float createTextureJPG(const std::string &Path);
  float createTexturePNG(const std::string &Path);
};

} // namespace mlh

#endif
