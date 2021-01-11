#include "GUITextMesh.hpp"


GUITextMesh::GUITextMesh(const std::string& string, const ColorRGBA8& c, unsigned int fontIndex){
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);

	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GUITextVertex), (void*)offsetof(GUITextVertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GUITextVertex), (void*)offsetof(GUITextVertex, uv));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_string = string;
	m_fontIndex = fontIndex;
	color = c;
}

unsigned int GUITextMesh::getFontIndex(){
	return m_fontIndex;
}

void GUITextMesh::setString(const std::string& string){
	m_string = string;
	needsUpdate = true;
}

void GUITextMesh::pushData(const std::vector<GUITextVertex>& vertices){
	m_numVertices = vertices.size();

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GUITextMesh::render(){
	glBindVertexArray(m_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
	glBindVertexArray(0);
}

void GUITextMesh::destroy(){
	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);
}
