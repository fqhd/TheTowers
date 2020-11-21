#pragma once
#include "Model.hpp"
#include "Transform.hpp"

class Entity {
public:

	Entity(const Transform& t, Model* m);
	void move(const glm::vec3& move);
	void render();

	Transform transform;

private:

	Model* m_model;

};
