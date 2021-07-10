#pragma once

#include "Shader.hpp"

class QuadShader : public Shader {
public:

    void init();
    void setToggle(bool _toggle);

private:

    void getUniformLocations();

    GLint m_toggleLocation = 0;

};
