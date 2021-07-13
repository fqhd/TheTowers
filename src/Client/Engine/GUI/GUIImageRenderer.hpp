#pragma once

#include "GUIImageShader.hpp"
#include "GUIImage.hpp"
#include <vector>

class GUIImageRenderer {
public:

    void init();
    void render();
    void destroy();

    std::vector<GUIImage> images;

private:
    GUIImageShader m_shader;


};
