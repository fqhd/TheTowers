#pragma once

#include "GUIImageShader.hpp"
#include "GUIImage.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class GUIImageRenderer {
public:

    void init();
    void renderImage(unsigned int _imageID);
    GLuint loadTexture(const std::string& path);
    void destroy();

    std::vector<GUIImage> images;
    std::vector<GLuint> textures;

private:


    GUIImageShader m_shader;


};
