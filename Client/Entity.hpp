#ifndef ENTITY_H
#define ENTITY_H
#include "Model.hpp"
#include "Transform.hpp"
#include "Vertex.hpp"


class Entity {
public:

	Entity(const Transform& t, Model* m, const ColorRGBA8& color);
	void move(const glm::vec3& move);
	void render();

	Transform transform;
	const ColorRGBA8& getColor() const;

private:

	ColorRGBA8 m_color;
	Model* m_model;

};

#endif
