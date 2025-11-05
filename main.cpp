#include "CheckboxButton.hpp"
#include "DeserializeJSON.hpp"
#include "PrintQuads.hpp"
#include "QuadGenerator.hpp"
#include "QuadUtils.hpp"
#include "Renderer.hpp"

int main() {
  // Top priority:
  // TODO: fix checkbox.
  // A checkbox overlapping another button SOMETIMES break the checkbox
  // button???
  //  Why does one of the checkbox images not work, but the other one
  // does?
  // Loading CheckedCheckbox.png before UncheckedCheckbox changed the
  // UncheckedCheckbox image slightly (pixels with random color in a line start
  // appearing). This could mean that texture loading is broken! (But why does
  // CheckedCheckboxThick.png always work?...)
  // TODO: check why x and y pos of quads are so weird. Draw a picture with
  // annotations on where what number is and how the screen is filled.
  // TODO: more features, which can and should be used for the app-builder.
  //       -> Slider for float values
  //       -> Input fields for numbers?
  //       -> Input fields for strings?
  //       -> Folder for images, that will be loaded when the app is started,
  //       that can be selected for buttons, the background, etc.
  //       -> Checkboxes
  //       Example: There should be a background editor. Either use sliders for
  //       the colors, or select an image to be used.
  // TODO: write guide how to include and use this project.
  // TODO: create a single header file that can and should be included to use
  // this project.
  // How to do the single include header? Make a script that stitches together
  // all header files into a single one?
  // -> how does that work with glad.c or stb_image.cpp?
  // Maybe look at nlohmann::json how it's done there.
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
  // TODO: add subfolders and sort files

  mlh::Renderer App = mlh::Renderer();

  App.setShader("../resources/Shaders/Vertex.shader",
                "../resources/Shaders/Fragment.shader");
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

  mlh::printQuad(Test);

  mlh::QuadButton Button1 = mlh::QuadButton(std::move(Test));

  App.addQuadButton(Button1);

  mlh::QuadGenerator::printBasicQuadValues();

  mlh::Quad BasicQuad = mlh::QuadGenerator::getBasicQuad();
  App.addQuad(BasicQuad);
#endif

  mlh::Quad QuadForCheckbox = mlh::QuadGenerator::getBasicQuad();

  // first button
  mlh::Vertex TestA = {0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
                       1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
  mlh::Vertex TestB = {0.5f, 0.5f, -1.0f, 1.0f, 1.0f,
                       1.0f, 1.0f, 1.0f,  0.0f, 0.0f};
  mlh::Vertex TestC = {0.5f, 1.0f, -1.0f, 1.0f, 1.0f,
                       1.0f, 1.0f, 1.0f,  1.0f, 0.0f};
  mlh::Vertex TestD = {0.0f, 1.0f, -1.0f, 1.0f, 1.0f,
                       1.0f, 1.0f, 0.0f,  1.0f, 0.0f};

  QuadForCheckbox.A = TestA;
  QuadForCheckbox.B = TestB;
  QuadForCheckbox.C = TestC;
  QuadForCheckbox.D = TestD;

  float TestForLoading =
      App.createTexture("../resources/Textures/CheckedCheckbox.png");
  float UncheckedCheckboxTexID =
      App.createTexture("../resources/Textures/UncheckedCheckbox.png");
  float CheckedCheckboxTexID =
      App.createTexture("../resources/Textures/CheckedCheckboxThick.png");

  mlh::changeQuadTexture(QuadForCheckbox, UncheckedCheckboxTexID);
  mlh::Quad UncheckedQuad = QuadForCheckbox;
  mlh::changeQuadTexture(QuadForCheckbox, CheckedCheckboxTexID);
  mlh::Quad CheckedQuad = QuadForCheckbox;

  // second button
  mlh::Quad QuadForCheckbox2 = mlh::QuadGenerator::getBasicQuad();

  mlh::Vertex TestA2 = {0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                        1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
  mlh::Vertex TestB2 = {1.0f, 0.5f, 0.0f, 1.0f, 1.0f,
                        1.0f, 1.0f, 1.0f, 0.0f, 0.0f};
  mlh::Vertex TestC2 = {1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                        1.0f, 1.0f, 1.0f, 1.0f, 0.0f};
  mlh::Vertex TestD2 = {0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
                        1.0f, 1.0f, 0.0f, 1.0f, 0.0f};

  QuadForCheckbox2.A = TestA2;
  QuadForCheckbox2.B = TestB2;
  QuadForCheckbox2.C = TestC2;
  QuadForCheckbox2.D = TestD2;

  mlh::Quad UncheckedQuad2 = QuadForCheckbox2;
  mlh::Quad CheckedQuad2 = QuadForCheckbox2;

  mlh::CheckboxButton TestCheckBox =
      mlh::CheckboxButton(UncheckedQuad, CheckedQuad);
  mlh::CheckboxButton TestCheckBox2 =
      mlh::CheckboxButton(UncheckedQuad2, CheckedQuad2);

  App.addCheckboxButton(TestCheckBox);
  // App.addCheckboxButton(TestCheckBox2);

  App.runLoop();

  return 0;
}
