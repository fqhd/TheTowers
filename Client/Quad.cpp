#include "Quad.hpp"

void Quad::init(){

     glGenVertexArrays(1, &m_vaoID);
     glBindVertexArray(m_vaoID);

     glGenBuffers(1, &m_vboID);
     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

}

void Quad::render(){
     glBindVertexArray(m_vaoID);
     glDrawTriangles(GL_TRIANGLES, 0, m_numVertices);
     glBindVertexArray(0);
}

void Quad::destroy(){
     glDeleteBuffers(1, &m_vboID);
     glDeleteVertexArrays(1, &m_vaoID);
}
