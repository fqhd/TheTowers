#ifndef PARTICLE_QUAD_H
#define PARTICLE_QUAD_H
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include "Vertex.hpp"

class ParticleQuad {
public:

    void init();
    void bind();
    void unbind();
    void render();
    void destroy();

    void pushMatrices(const std::vector<glm::mat4>& matrices);
    void pushColors(const std::vector<vec3>& colors);



private:

    GLuint m_vaoID;
    GLuint m_vboID;
    GLuint m_ivboID;
    GLuint m_colorsVBOID;


};

#endif
