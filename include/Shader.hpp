#ifndef MLH_RENDERER_SHADER_HPP
#define MLH_RENDERER_SHADER_HPP

#include <iostream>
#include <string>

#include "FileReader.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "glad/glad.h"

namespace mlh {

class Shader {
public:
  unsigned int ID;

  Shader() : ID() {}
  Shader(const std::string &vertexShaderPath,
         const std::string &fragmentShaderPath)
      : isDefault(false) {
    std::string vertexShaderString;
    std::string fragmentShaderString;
    FileReader::readFromFile(vertexShaderString, vertexShaderPath);
    FileReader::readFromFile(fragmentShaderString, fragmentShaderPath);
    const char *vscc = vertexShaderString.c_str();
    const char *fscc = fragmentShaderString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vscc, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShader, 1, &fscc, NULL);
    glCompileShader(fragmentShader);
    // Checking if everything worked with the shader
    char infoLog[512];
    int success;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "[ERROR]: Vertex shader compilation failed\n"
                << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "[ERROR]: Fragment shader compilation failed\n"
                << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      std::cout << "[ERROR]: Shader compilation failed\n"
                << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
  }

  ~Shader() {}

  bool isDefault = true;

  void use() { glUseProgram(ID); }

  // utility uniform functions
  void setBool(const std::string &name, const bool &value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
  }

  void setInt(const std::string &name, const int &value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }

  void setUnsignedInt(const std::string &name, const int &value) const {
    glUniform1ui(glGetUniformLocation(ID, name.c_str()), value);
  }

  void setFloat(const std::string &name, const float &value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }

  void setMat4(const std::string &name, const glm::mat4 &value,
               GLboolean transpose) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, transpose,
                       glm::value_ptr(value));
  }

  void setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
  }

  void setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
  }
  void setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
  }
  void setSampler2D(const std::string &name, const unsigned int &value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }
};

} // namespace mlh

#endif
