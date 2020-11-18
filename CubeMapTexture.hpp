#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>

class CubeMapTexture {
public:

    void init(const std::vector<std::string>& locations);
    void bind();
    void unbind();
    void destroy();

private:

    GLuint m_textureID;

};