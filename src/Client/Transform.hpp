#pragma once

#include "Math.hpp"

class Transform {
public:

	Transform();

	void setPosition(const math::vec3& _position);
	void setRotation(const math::vec3& _rotation);
	void setScale(const math::vec3& _scale);

	const math::vec3& getPosition() const;
	const math::vec3& getRotation() const;
	const math::vec3& getScale() const;

	void move(const math::vec3& _delta);

	math::mat4 getMatrix() const;

private:

	bool m_needsUpdate = true;
	math::vec3 m_position;
	math::vec3 m_rotation;
	math::vec3 m_scale;

};