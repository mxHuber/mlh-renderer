#include "DeserializeJSON.hpp"
#include "PrintQuads.hpp"
#include "QuadGenerator.hpp"
#include "Renderer.hpp"

// settings
unsigned int WindowWidth = 800;
unsigned int WindowHeight = 600;

int main() {
  // Top priority:
  // TODO: write guide how to include and use this project.
  // TODO: create a single header file that can and should be included to use
  // this project.
  // TODO: create a software with this app where buttons can be placed with
  // certain functions. All this data then should be serialized.
  // This should on one hand serve as a tool to make applications, but on the
  // other hand also be a good test for using this as an external software and
  // to check if it can be implemented well into existing projects.
  //
  // Low priority:
  // TODO: third value in position is currently not used.
  // Find out if it can be used for layering, aka determine what should render
  // infront, if there are overlapping sprites
  //
  // TODO: add subfolders and sort files

  mlh::Renderer App = mlh::Renderer();

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
  mlh::Vertex TestA = {0.4f, 0.6f, -1.0f, 1.0f, 0.0f,
                       0.0f, 1.0f, 0.0f,  0.0f, 0.0f};
  mlh::Vertex TestB = {0.6f, 0.6f, -1.0f, 0.0f, 1.0f,
                       0.0f, 1.0f, 1.0f,  0.0f, 0.0f};
  mlh::Vertex TestC = {0.6f, 0.8f, -1.0f, 0.0f, 0.0f,
                       1.0f, 0.0f, 1.0f,  1.0f, 0.0f};
  mlh::Vertex TestD = {0.4f, 0.8f, -1.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f,  1.0f, 0.0f};

  mlh::Quad Test = {TestA, TestB, TestC, TestD};

  mlh::printQuad(Test);

#if false
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
