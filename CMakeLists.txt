cmake_minimum_required (VERSION 3.14)
project(renderer)
find_package(OpenGL REQUIRED)

add_executable(renderer main.cpp glad.c lib/Renderer.cpp lib/FileReader.cpp lib/InitOpenGL.cpp lib/QuadButton.cpp lib/QuadGenerator.cpp lib/RectangleRenderer.cpp lib/Shader.cpp lib/stb_image.cpp lib/Window.cpp lib/MouseButtons.cpp lib/Keys.cpp lib/DeserializeJSON.cpp)

target_include_directories(renderer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/externals/json/single_include")
target_link_libraries(renderer glfw)
