#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H
#include <glm/glm.hpp>
#include <vector>
#include "glad.h"
#include "Vertex.hpp"
#include "Utils.hpp"

class GUIRenderer {
public:

    void init();
    void begin();
    void draw(const glm::vec4& destRect, const ColorRGBA8& color);
    void end();
    void render();

    void destroy();


private:


    void uploadData();
    void createVAO();

    GLuint m_vbo = 0;
    GLuint m_vao = 0;

    std::vector<GUIVertex> m_vertices;
};

#endif
