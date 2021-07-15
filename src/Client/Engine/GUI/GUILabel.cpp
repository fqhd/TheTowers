#include "GUILabel.hpp"
#include "../Utils/Utils.hpp"


GUILabel::GUILabel(){

}

GUILabel::GUILabel(const std::string& string, const glm::vec2& p, const ColorRGBA8& c){
	init(string, p, c);
}

void GUILabel::init(const std::string& string, const glm::vec2& p, const ColorRGBA8& c){
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
	color = c;
	position = p;
}

void GUILabel::setString(const std::string& string){
	m_string = string;
	needsMeshUpdate = true;
}

void GUILabel::pushData(const std::vector<GUITextVertex>& vertices){
	m_numVertices = vertices.size();

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GUILabel::render(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glBindVertexArray(m_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
	glBindVertexArray(0);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void GUILabel::destroy(){
	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);
}

const std::string& GUILabel::getString(){
	return m_string;
}
