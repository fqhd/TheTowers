#ifndef PARTICLE_SHADER_H
#define PARTICLE_SHADER_H
#include "Shader.hpp"
#include <glm/glm.hpp>

class ParticleShader : public Shader {
public:

  void init();

  void loadProjection(const glm::mat4& matrix);

private:

  void getUniformLocations();
  GLint m_projectionLocation = 0;

};

#endif
