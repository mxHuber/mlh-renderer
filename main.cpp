#include "CheckboxButton.hpp"
#include "DeserializeJSON.hpp"
#include "Menu.hpp"
#include "PrintQuads.hpp"
#include "QuadGenerator.hpp"
#include "QuadUtils.hpp"
#include "Renderer.hpp"

int main() {
  // Top priority:
  // TODO: Fix transparency. Example: A png with a transparent section will be
  // drawn with that section as 100% opaque. So it will not blend with what's
  // behind it.
  // TODO: Serialization for new features like Menus, CheckboxButtons, etc
  // TODO: saveAppAsJSON function

  // Medium priority:
  // TODO: add texture path to json for buttons, etc.
  //       -> Also add the loading of those in the DeserializeJSON.hpp file.
  // TODO: add functions to set in the constructor of CheckboxButtons
  // TODO: fix checkboxes.
  // A checkbox overlapping another button SOMETIMES break the checkbox
  // button???
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
  //       -> Don't put everything in header files.
  // TODO: create a software with this app where buttons can be placed with
  // certain functions. All this data then should be serialized.
  // This should on one hand serve as a tool to make applications, but on the
  // other hand also be a good test for using this as an external software and
  // to check if it can be implemented well into existing projects.

  // Low priority:
  // TODO: Where to store the data? Currently most stuff is created in the main
  // function and an address is given to the app. Maybe move the data to the
  // app? That way, if the app is out of scope, all data of it gets removed as
  // well.
  // TODO: third value in position is currently not used.
  // !--> Apparently it is used, but it acts very weird.
  // Find out if it can be used for layering, aka determine what should render
  // infront, if there are overlapping sprites
  // TODO: add subfolders and sort files
  // TODO: maybe add functionality to make a checkbox button with a colored
  // texture?

  mlh::Renderer App = mlh::Renderer();

  App.setShader("../resources/Shaders/Vertex.shader",
                "../resources/Shaders/Fragment.shader");
  mlh::DeserializeJSON::deserializeJSON("../resources/Files/test_app_1.json",
                                        App);

  // Menu

  mlh::Quad QuadForMenu = mlh::QuadGenerator::getBasicQuad();

  mlh::Vertex TestMenuA = {0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
                           1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
  mlh::Vertex TestMenuB = {1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                           1.0f, 1.0f, 0.0f, 1.0f, 0.0f};
  mlh::Vertex TestMenuC = {1.0f, 0.5f, 0.0f, 1.0f, 1.0f,
                           1.0f, 1.0f, 1.0f, 1.0f, 0.0f};
  mlh::Vertex TestMenuD = {0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                           1.0f, 1.0f, 1.0f, 0.0f, 0.0f};
  QuadForMenu.A = TestMenuA;
  QuadForMenu.B = TestMenuB;
  QuadForMenu.C = TestMenuC;
  QuadForMenu.D = TestMenuD;

  float MenuBackgroundTexID =
      App.createTexture("../resources/Textures/TestMenuBackground.png");

  mlh::changeQuadTexture(QuadForMenu, MenuBackgroundTexID);

  mlh::Menu TestMenu = mlh::Menu(200.0f, 500.0f, QuadForMenu);

  App.addMenu(TestMenu);

  App.runLoop();

  return 0;
}
