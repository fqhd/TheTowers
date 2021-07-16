#pragma once

#include "../Math/Math.hpp"


class Transform {
public:

	Transform();
	Transform(const math::vec3& position, const math::vec3& rotation, const math::vec3& scale);
	void init(const math::vec3& position, const math::vec3& rotation, const math::vec3& scale);
	const math::mat4& getMatrix();

	void setPosition(const math::vec3& position);
	void setRotation(const math::vec3& rotation);
	void setScale(const math::vec3& scale);

	void move(const math::vec3& delta);

	const math::vec3& getPosition() const;
	const math::vec3& getRotation() const;
	const math::vec3& getScale() const;

private:

	bool m_needsUpdate = true;

	math::vec3 m_position;
	math::vec3 m_rotation;
	math::vec3 m_scale;

	math::mat4 m_matrix;

};


