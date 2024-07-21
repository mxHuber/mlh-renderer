#ifndef EXREND2D_INIT_OPENGL_HPP
#define EXREND2D_INIT_OPENGL_HPP

class InitOpenGL {
public:
  static void initializeGlfw();
  static void initializeGlad();
  static void initializeSettings();

private:
  static bool GlfwIsInitialized;
  static bool GladIsInitialized;
};

#endif
