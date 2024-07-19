cmake_minimum_required (VERSION 3.14)
project(exrend2d)
find_package(OpenGL REQUIRED)

add_executable(exrend2d main.cpp glad.c lib/stb_image.cpp)

target_include_directories(exrend2d PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(exrend2d glfw)

