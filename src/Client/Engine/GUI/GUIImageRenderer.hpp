#pragma once

#include "GUIImageShader.hpp"
#include "GUIImage.hpp"
#include <vector>

class GUIImageRenderer {
public:

    void init();
    void renderImage(unsigned int _imageID);
    void addTexture(const std::string& _path);
    void addImage(const math::vec4& _destRect, unsigned int _index);
    void destroy();


private:

    GLuint loadTexture(const std::string& _path);
    std::vector<GLuint> m_textures;
    std::vector<GUIImage> m_images;


    GUIImageShader m_shader;


};
