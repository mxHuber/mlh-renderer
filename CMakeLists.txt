cmake_minimum_required (VERSION 3.14)
project(renderer)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(OpenGL REQUIRED)

add_executable(renderer main.cpp external/manually_added/glad/glad.c external/manually_added/stb_image/stb_image.cpp)

target_include_directories(renderer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/external/json/single_include")
target_link_libraries(renderer glfw)
