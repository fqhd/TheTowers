#pragma once

#include "../Utils/Shader.hpp"
#include "../Math/Math.hpp"

class GUIImageShader : public Shader {
public:

    void init();

    void loadMatrix(const math::mat4& matrix);
    void loadPosition(const math::vec2& position);

private:

    void getUniformLocations();

    GLint m_positionLocation = 0;
    GLint m_matrixLocation = 0;

};
