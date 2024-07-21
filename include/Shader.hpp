#ifndef EXREND2D_SHADER_HPP
#define EXREND2D_SHADER_HPP

#include <string>

struct Shader {
  unsigned int ID;

  Shader();
  Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
  ~Shader();
  void use();

  // utility uniform functions
  void setBool(const std::string &name, const bool &value) const;
  void setInt(const std::string &name, const int &value) const;
  void setUnsignedInt(const std::string &name, const int &value) const;
  void setFloat(const std::string &name, const float &value) const;
#if false
  void setMat4(const std::string &name, const glm::mat4 &value,
               GLboolean transpose) const;
  void setVec2(const std::string &name, const glm::vec2 &value) const;
  void setVec3(const std::string &name, const glm::vec3 &value) const;
  void setVec4(const std::string &name, const glm::vec4 &value) const;
#endif
  void setSampler2D(const std::string &name, const unsigned int &value) const;
};

#endif
