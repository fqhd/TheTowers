#include "Model.hpp"
#include "OBJLoader.hpp"
#include "Utils.hpp"


void Model::loadFromFile(const std::string& path){

     //Initializing the vao
     glGenVertexArrays(1, &m_vaoID);
     glBindVertexArray(m_vaoID);

     glGenBuffers(1, &m_vboID);
     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

     glEnableVertexAttribArray(0);
     glEnableVertexAttribArray(1);

     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)offsetof(ModelVertex, position));
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)offsetof(ModelVertex, normal));

     //Creating and sending data to VBO
     IndexedModel model = OBJModel(path).ToIndexedModel();
     std::vector<ModelVertex> vertices;
     for(unsigned int i = 0; i < model.positions.size(); i++){
          vertices.emplace_back(model.positions[i], model.normals[i]);
     }

     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glBindVertexArray(0);

     //Making EBO object
     glGenBuffers(1, &m_eboID);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), model.indices.data(), GL_STATIC_DRAW);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

     m_numVertices = model.indices.size();

     Utils::log("Loaded model " + path + " with " + std::to_string(m_numVertices) + " vertices");

}

GLuint Model::getNumVertices(){
     return m_numVertices;
}

GLuint Model::getVaoID(){
     return m_vaoID;
}

GLuint Model::getVboID(){
     return m_eboID;
}

GLuint Model::getEboID(){
     return m_eboID;
}

void Model::render(){
     glBindVertexArray(m_vaoID);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
     glDrawElements(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, 0);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
     glBindVertexArray(0);
}

void Model::destroy(){
     glDeleteVertexArrays(1, &m_vaoID);
     glDeleteBuffers(1, &m_vboID);
     glDeleteBuffers(1, &m_eboID);
}
