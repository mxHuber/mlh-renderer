#ifndef MLH_RENDERER_INIT_OPENGL_HPP
#define MLH_RENDERER_INIT_OPENGL_HPP

#include <iostream>
// glad must be included first
#include <glad/glad.h>
// then glfw afterwards
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

namespace mlh {

class InitOpenGL {
public:
  static void initializeGlfw() {
    if (GlfwIsInitialized) {
      return;
    }

    // glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GlfwIsInitialized = true;
  }

  static void initializeGlad() {
    if (GladIsInitialized) {
      return;
    }

    // glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialise GLAD" << std::endl;
      abort();
    }

    GladIsInitialized = true;
  }

  static void initializeSettings() {
    // settings
    glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA); //is SUPER funny :D
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // stb image
    stbi_set_flip_vertically_on_load(true);

    // anti aliasing
    glEnable(GL_MULTISAMPLE);
  }

private:
  inline static bool GlfwIsInitialized = false;
  inline static bool GladIsInitialized = false;
};

} // namespace mlh

#endif
