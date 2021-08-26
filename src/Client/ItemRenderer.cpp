#include "ItemRenderer.hpp"

const unsigned int ITEM_WIDTH = 32;

void ItemRenderer::init(){
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ItemVertex), (void*)offsetof(ItemVertex, position));
	glVertexAttribPointer(1, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(ItemVertex), (void*)offsetof(ItemVertex, uv));
	glBindVertexArray(0);

	glGenBuffers(1, &m_vboID);
}

void ItemRenderer::begin(){
	m_vertices.clear();
}

void ItemRenderer::draw(const math::vec2& _area, unsigned int _uv){
	m_vertices.emplace_back(math::vec2(_area.x, _area.y), _uv);
	m_vertices.emplace_back(math::vec2(_area.x, _area.y + ITEM_WIDTH), _uv);
	m_vertices.emplace_back(math::vec2(_area.x + ITEM_WIDTH, _area.y + ITEM_WIDTH), _uv);

	m_vertices.emplace_back(math::vec2(_area.x, _area.y), _uv);
	m_vertices.emplace_back(math::vec2(_area.x + ITEM_WIDTH, _area.y + ITEM_WIDTH), _uv);
	m_vertices.emplace_back(math::vec2(_area.x + ITEM_WIDTH, _area.y), _uv);
}

void ItemRenderer::end(){
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), m_vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ItemRenderer::render(){
	glBindVertexArray(m_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	glBindVertexArray(0);
}

void ItemRenderer::destroy(){
	m_vertices.clear();
	glDeleteVertexArrays(1, &m_vaoID);
	glDeleteBuffers(1, &m_vboID);
}
