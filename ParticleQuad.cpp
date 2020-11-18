#include "ParticleQuad.hpp"
#include <glm/glm.hpp>

void ParticleQuad::init(){
     float vertices[] = {
          -0.5f, -0.5f,
          -0.5f, 0.5f,
          0.5f, 0.5f,
          -0.5f, -0.5f,
          0.5f, 0.5f,
          0.5f, -0.5f
     };

     glGenVertexArrays(1, &m_vaoID);
     glBindVertexArray(m_vaoID);

     glGenBuffers(1, &m_vboID);
     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);


     glGenBuffers(1, &m_ivboID);
     glBindBuffer(GL_ARRAY_BUFFER, m_ivboID);
     glEnableVertexAttribArray(1);
     glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
     glEnableVertexAttribArray(2);
     glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
     glEnableVertexAttribArray(3);
     glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
     glEnableVertexAttribArray(4);
     glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

     glVertexAttribDivisor(1, 1);
     glVertexAttribDivisor(2, 1);
     glVertexAttribDivisor(3, 1);
     glVertexAttribDivisor(4, 1);

     glBindBuffer(GL_ARRAY_BUFFER, 0);

     glGenBuffers(1, &m_colorsVBOID);
     glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBOID);

     glEnableVertexAttribArray(5);
     glVertexAttribPointer(5, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vec3), 0);

     glVertexAttribDivisor(5, 1);

     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glBindVertexArray(0);

}

void ParticleQuad::pushMatrices(const std::vector<glm::mat4>& matrices){
     glBindBuffer(GL_ARRAY_BUFFER, m_ivboID);
     glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(matrices[0]), matrices.data(), GL_STREAM_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleQuad::pushColors(const std::vector<vec3>& colors){
     glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBOID);
     glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(colors[0]), colors.data(), GL_STREAM_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleQuad::bind(){
     glBindVertexArray(m_vaoID);
}

void ParticleQuad::unbind(){
     glBindVertexArray(0);
}

void ParticleQuad::render(){
     glDrawArrays(GL_TRIANGLES, 0, 6);
}

void ParticleQuad::destroy(){
     glDeleteVertexArrays(1, &m_vaoID);
     glDeleteBuffers(1, &m_vboID);
}
