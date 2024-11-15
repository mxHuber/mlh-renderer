#include "QuadGenerator.hpp"
#include "Renderer.hpp"

// settings
const unsigned int WindowWidth = 800;
const unsigned int WindowHeight = 600;

int main() {
  // TODO: third value in position is currently not used.
  // Find out if it can be used for layering, aka determine what should render
  // infront, if there are overlapping sprites

  mlh::Renderer App = mlh::Renderer();

  App.setShader("../resources/Shaders/Vertex.shader",
                "../resources/Shaders/Fragment.shader");
  App.addQuad(mlh::QuadGenerator::getBasicQuad());
  // App.addQuad(mlh::QuadGenerator::getRandomQuad());
  // float BackgroundImageID =
  //    App.createTexture("../resources/Textures/test64x64.png");
  // float BackgroundImageID =
  //    App.createTexture("../resources/Textures/BackgroundImage.png");
  float BackgroundImageID =
      App.createTexture("../resources/Textures/BackgroundImage.jpg");
  App.setBackground(BackgroundImageID);

  App.runLoop();

  return 0;
}
