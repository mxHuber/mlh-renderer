#ifndef MLH_RENDERER_RECTANGLE_RENDERER_HPP
#define MLH_RENDERER_RECTANGLE_RENDERER_HPP

#include <array>
#include <iostream>
// glad must be included first
#include <glad/glad.h>
// then glfw afterwards
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

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
  RectangleRenderer(int WindowWidth, int WindowHeight)
      : WindowWidth(WindowWidth), WindowHeight(WindowHeight) {
    if (!RecShader.isDefault) {
      init();
    }
  }

  float createTexture(const std::string &Path) {
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

  void addToBatch(const Quad &ToAdd) {
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

  void drawBatch() {
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

  void resetData() {
    VerticesIndex = 0;
    IndicesCounter = 0;
  }

  void setShader(const std::string &Vertex, const std::string &Fragment) {
    RecShader = Shader(Vertex, Fragment);
    std::cout << "Shader set!" << std::endl;

    if (!isInitialized) {
      init();
    }
  }

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

  void checkForOpenGLErrors(const std::string &AdditionalInfo = "") {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
      if (AdditionalInfo == "") {
        std::cerr << "OpenGL error: " << err << std::endl;
        continue;
      }
      std::cerr << "Info: " << AdditionalInfo << "\nOpenGL error: " << err
                << std::endl;
    }
  }
  void init() {
    // setup samplers in the fragment shader
    RecShader.use();
    auto Loc = glGetUniformLocation(RecShader.ID, "Textures");

    checkForOpenGLErrors("After glGetUniformLocation");

    int Samplers[16];
    for (int i = 0; i < 16; i++)
      Samplers[i] = i;
    glUniform1iv(Loc, 16, Samplers);

    checkForOpenGLErrors("After glUniform1iv");

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

    checkForOpenGLErrors("After white texture generation");

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

    checkForOpenGLErrors("After VertexAttrib initialization");

    free(indices);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "[RectangleRenderer::ctor] OpenGL error: " << err
                << std::endl;
    }

    isInitialized = true;
  }

  float createTextureJPG(const std::string &Path) {
    unsigned int Texture;

    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);
    checkForOpenGLErrors("[createTextureJPG]: After glBindTexture");
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
      checkForOpenGLErrors("[createTextureJPG]: After glGenerateMipmap");
    } else {
      std::cerr << "Failed to load texture" << std::endl;
    }

    stbi_image_free(Data);

    return (float)TextureSlotIndex++;
  }

  float createTexturePNG(const std::string &Path) {
    unsigned int Texture;

    glCreateTextures(GL_TEXTURE_2D, 1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);
    checkForOpenGLErrors("[createTexturePNG]: After glBindTexture");
    TextureSlots[TextureSlotIndex] = Texture;

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int Width, Height, NrChannels;
    // load image, create texture and generate mipmaps
    unsigned char *Data =
        stbi_load(Path.c_str(), &Width, &Height, &NrChannels, 0);
    if (Data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, Data);
      glGenerateMipmap(GL_TEXTURE_2D);
      checkForOpenGLErrors("[createTexturePNG]: After glGenerateMipmap");
    } else {
      std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(Data);

    return (float)TextureSlotIndex++;
  }
};

} // namespace mlh

#endif
