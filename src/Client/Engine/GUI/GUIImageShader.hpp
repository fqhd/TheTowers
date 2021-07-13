#pragma once

#include "../Utils/Shader.hpp"
#include <glm/glm.hpp>

class GUIImageShader : public Shader {
public:

    void init();

    void loadPosition(const glm::vec2& position);

private:

    void getUniformLocations();

    GLint m_positionLocation = 0;

};
