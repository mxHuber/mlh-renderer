#include "DeserializeJSON.hpp"
#include "QuadGenerator.hpp"
#include "Renderer.hpp"

// settings
unsigned int WindowWidth = 800;
unsigned int WindowHeight = 600;

int main() {
  // TODO: third value in position is currently not used.
  // Find out if it can be used for layering, aka determine what should render
  // infront, if there are overlapping sprites
  //
  // Create a function that prints quads, quadButtons, etc as json objects to
  // the console

  mlh::Renderer App = mlh::Renderer();

  // Test if passing a string like that works, as deserializeJSON() takes a
  // string address as an argument

  App.setShader("../resources/Shaders/Vertex.shader",
                "../resources/Shaders/Fragment.shader");
  // App.addQuad(mlh::QuadGenerator::getBasicQuad());
  // App.addQuad(mlh::QuadGenerator::getRandomQuad());
  // float BackgroundImageID =
  //    App.createTexture("../resources/Textures/test64x64.png");
  // float BackgroundImageID =
  //    App.createTexture("../resources/Textures/BackgroundImage.png");
  mlh::DeserializeJSON::deserializeJSON("../resources/Files/test_app_1.json",
                                        App);
#if false
  mlh::Vertex TestA = {0.4f, 0.6f, -1.0f, 1.0f, 0.0f,
                       0.0f, 1.0f, 0.0f,  0.0f, 0.0f};
  mlh::Vertex TestB = {0.6f, 0.6f, -1.0f, 0.0f, 1.0f,
                       0.0f, 1.0f, 1.0f,  0.0f, 0.0f};
  mlh::Vertex TestC = {0.6f, 0.8f, -1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 1.0f,  1.0f, 0.0f};
  mlh::Vertex TestD = {0.4f, 0.8f, -1.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f,  1.0f, 0.0f};

  mlh::Quad Test = {TestA, TestB, TestC, TestD};

  mlh::QuadButton Button1 =
      mlh::QuadButton(std::move(Test), WindowWidth, WindowHeight);

  App.addButton(Button1);

  mlh::QuadGenerator::printBasicQuadValues();

  mlh::Quad BasicQuad = mlh::QuadGenerator::getBasicQuad();
  App.addQuad(BasicQuad);
#endif

  App.runLoop();

  return 0;
}
