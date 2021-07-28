#include "Model.hpp"

#include <iostream>

void Model::init(const std::string& path){
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);

	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)offsetof(ModelVertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)offsetof(ModelVertex, normal));

	// Loading the data and sending it to the GPU
	IndexedModel model = OBJModel(path).ToIndexedModel();
	std::vector<ModelVertex> vertices;
	for(unsigned int i = 0; i < model.positions.size(); i++){
		vertices.emplace_back(
			model.positions[i],
			model.normals[i]
		);
	}
	std::cout << "size of mode: " << vertices.size() << std::endl;
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenBuffers(1, &m_eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), model.indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_numVertices = model.indices.size();
}

void Model::render() const {
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
