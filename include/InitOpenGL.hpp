#ifndef MLH_RENDERER_INIT_OPENGL_HPP
#define MLH_RENDERER_INIT_OPENGL_HPP

namespace mlh {

class InitOpenGL {
public:
  static void initializeGlfw();
  static void initializeGlad();
  static void initializeSettings();

private:
  static bool GlfwIsInitialized;
  static bool GladIsInitialized;
};

} // namespace mlh

#endif
