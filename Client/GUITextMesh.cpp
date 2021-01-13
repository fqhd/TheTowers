#include "GUITextMesh.hpp"
#include "Utils.hpp"


GUITextMesh::GUITextMesh(const std::string& string, const glm::vec2& p, const ColorRGBA8& c, unsigned int fontIndex){
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
	position = p;
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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GUITextVertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GUITextMesh::render(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glBindVertexArray(m_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
	glBindVertexArray(0);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void GUITextMesh::destroy(){
	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);
}

const std::string& GUITextMesh::getString(){
	return m_string;
}
