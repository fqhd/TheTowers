#pragma once

#include "GUIImageShader.hpp"
#include "GUIImage.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class GUIImageRenderer {
public:

    void init();
    void renderImage(unsigned int _imageID);
    void addTexture(const std::string& _path);
    void addImage(const glm::vec4& _destRect, GLuint _index);
    void destroy();


private:

    GLuint loadTexture(const std::string& _path);
    std::vector<GLuint> m_textures;
    std::vector<GUIImage> m_images;


    GUIImageShader m_shader;


};
