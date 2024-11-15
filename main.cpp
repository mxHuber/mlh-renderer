#include "Renderer.hpp"

// settings
unsigned int WindowWidth = 800;
unsigned int WindowHeight = 600;

int main() {
  // TODO: third value in position is currently not used.
  // Find out if it can be used for layering, aka determine what should render
  // infront, if there are overlapping sprites

  mlh::Renderer App = mlh::Renderer();

  App.setShader("../resources/Shaders/Vertex.shader",
                "../resources/Shaders/Fragment.shader");
  // App.addQuad(mlh::QuadGenerator::getBasicQuad());
  // App.addQuad(mlh::QuadGenerator::getRandomQuad());
  // float BackgroundImageID =
  //    App.createTexture("../resources/Textures/test64x64.png");
  // float BackgroundImageID =
  //    App.createTexture("../resources/Textures/BackgroundImage.png");
  float BackgroundImageID =
      App.createTexture("../resources/Textures/BackgroundImage.jpg");
  App.setBackground(BackgroundImageID);

  mlh::Vertex TestA = {0.2f, 0.2f, -1.0f, 1.0f, 0.0f,
                       0.0f, 1.0f, 0.0f,  0.0f, 0.0f};
  mlh::Vertex TestB = {0.4f, 0.2f, -1.0f, 0.0f, 1.0f,
                       0.0f, 1.0f, 1.0f,  0.0f, 0.0f};
  mlh::Vertex TestC = {0.4f, 0.4f, -1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 1.0f,  1.0f, 0.0f};
  mlh::Vertex TestD = {0.2f, 0.4f, -1.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f,  1.0f, 0.0f};

  mlh::Quad Test = {TestA, TestB, TestC, TestD};

  mlh::QuadButton Button1 =
      mlh::QuadButton(std::move(Test), WindowWidth, WindowHeight);

  App.addButton(Button1);

  App.runLoop();

  return 0;
}
