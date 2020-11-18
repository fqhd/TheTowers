#pragma once
#include "Shader.hpp"
#include <glm/glm.hpp>

class ParticleShader : public Shader {
public:

    void getUniformLocations();
    void loadProjection(const glm::mat4& matrix);

private:

    GLint m_projectionLocation = 0;

};
