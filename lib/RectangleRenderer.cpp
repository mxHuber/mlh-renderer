#include "RectangleRenderer.hpp"
#include <iostream>
// glad must be included first
#include <glad/glad.h>
// then glfw afterwards
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

namespace mlh {

RectangleRenderer::RectangleRenderer(int WindowWidth, int WindowHeight)
    : WindowWidth(WindowWidth), WindowHeight(WindowHeight) {
  if (!RecShader.isDefault) {
    init();
  }
}

float RectangleRenderer::createTexture(const std::string &Path) {
  float TextureIndex = 0;

  if (Path.substr(Path.length() - 4, Path.length() - 1) == ".png") {
    TextureIndex = createTexturePNG(Path);
  } else if ((Path.substr(Path.length() - 4, Path.length() - 1) == ".jpg") ||
             (Path.substr(Path.length() - 5, Path.length() - 1) == ".jpeg")) {
    TextureIndex = createTextureJPG(Path);
  } else {
    std::cout
        << "[RectangleRenderer::createTexture]: file extension not supported."
        << std::endl;
  }

  return TextureIndex;
}

void RectangleRenderer::addToBatch(const Quad &ToAdd) {
  if (VerticesIndex >= MaxQuads - 4) {
    drawBatch();
  }

  Vertices[VerticesIndex++] = ToAdd.A;
  Vertices[VerticesIndex++] = ToAdd.B;
  Vertices[VerticesIndex++] = ToAdd.C;
  Vertices[VerticesIndex++] = ToAdd.D;

  // For every 4 vertices we have 6 indices
  IndicesCounter += 6;
}

void RectangleRenderer::drawBatch() {
  RecShader.use();

  RecShader.setInt("windowWidth", WindowWidth);
  RecShader.setInt("windowHeight", WindowHeight);

  for (unsigned int i = 0; i < TextureSlotIndex; i++) {
    glBindTextureUnit(i, TextureSlots[i]);
  }

  // Set dynamic vertex buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices);

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, IndicesCounter, GL_UNSIGNED_INT, 0);

  VerticesIndex = 0;
  IndicesCounter = 0;
}

void RectangleRenderer::resetData() {
  VerticesIndex = 0;
  IndicesCounter = 0;
}

void RectangleRenderer::init() {
  // setup samplers in the fragment shader
  RecShader.use();
  auto Loc = glGetUniformLocation(RecShader.ID, "Textures");

  int Samplers[16];
  for (int i = 0; i < 16; i++)
    Samplers[i] = i;
  glUniform1iv(Loc, 16, Samplers);

  /*
          In the shader we always mix a texture with a
          color, so we can always draw textures and tint
          them as we like. However, we can also draw a
          color on it's own by mixing it with a white
          1x1 pixel texture, which is created below.
  */
  glGenTextures(1, &WhiteTexture);
  glBindTexture(GL_TEXTURE_2D, WhiteTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  unsigned int WhiteColor = 0xffffffff;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               &WhiteColor);

  TextureSlots[0] = WhiteTexture;
  for (int i = 1; i < MaxTextures; i++) {
    TextureSlots[i] = 0;
  }

  unsigned int *indices =
      (unsigned int *)malloc(MaxIndices * sizeof(unsigned int));
  unsigned int offset = 0;

  if (indices != NULL) {
    for (int i = 0; i < MaxIndices; i += 6) {
      indices[i + 0] = 0 + offset;
      indices[i + 1] = 1 + offset;
      indices[i + 2] = 2 + offset;
      indices[i + 3] = 2 + offset;
      indices[i + 4] = 3 + offset;
      indices[i + 5] = 0 + offset;
      offset += 4;
    }
  }

  // initialisation
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // we use nullptr here, because that way we simply reserve memory space. Due
  // to GL_DYNAMIC_DRAW we can populate that space with data at any time
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MaxVertices, nullptr,
               GL_DYNAMIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // Do NOT use 'sizeof(indices)', that returns the size of the pointer type
  // (probably ~ 4 - 8)! Just type in the same of what you put in the malloc()
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxIndices * sizeof(unsigned int),
               indices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0); // Could just do 0 here, however if we change
                                // the struct this here is still working
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, Position));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, Color));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, TexCoords));

  free(indices);

  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cerr << "[RectangleRenderer::ctor] OpenGL error: " << err << std::endl;
  }

  isInitialized = true;
}

float RectangleRenderer::createTextureJPG(const std::string &Path) {
  unsigned int Texture;

  glGenTextures(1, &Texture);
  glBindTexture(GL_TEXTURE_2D, Texture);
  TextureSlots[TextureSlotIndex] = Texture;

  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int Width, Height, NrChannels;
  // load image, create texture and generate mipmaps
  unsigned char *Data =
      stbi_load(Path.c_str(), &Width, &Height, &NrChannels, 0);
  if (Data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, Data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cerr << "Failed to load texture" << std::endl;
  }

  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cerr << "[createTextureJPG] OpenGL error: " << err << std::endl;
  }

  stbi_image_free(Data);

  return (float)TextureSlotIndex++;
}

float RectangleRenderer::createTexturePNG(const std::string &Path) {
  unsigned int texture;

  glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  TextureSlots[TextureSlotIndex] = texture;

  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  // load image, create texture and generate mipmaps
  unsigned char *Data =
      stbi_load(Path.c_str(), &width, &height, &nrChannels, 0);
  if (Data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA8,
                 GL_UNSIGNED_BYTE, Data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }

  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cerr << "[createTexturePNG] OpenGL error: " << err << std::endl;
  }

  stbi_image_free(Data);

  return (float)TextureSlotIndex++;
}

void RectangleRenderer::setShader(const std::string &Vertex,
                                  const std::string &Fragment) {
  RecShader = Shader(Vertex, Fragment);
  std::cout << "Shader set!" << std::endl;

  if (!isInitialized) {
    init();
  }
}

} // namespace mlh
