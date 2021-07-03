#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <glm/matrix.hpp>

// This is NOT my code
// This is a modification of this class: https://gist.github.com/podgorskiy/e698d18879588ada9014768e3e82a644
// The original author is Stanislav Pidhorskyi and here is his github: https://gist.github.com/podgorskiy

class Frustum {
public:
	Frustum() {}

	// m = ProjectionMatrix * ViewMatrix
	void update(glm::mat4 m);

	// http://iquilezles.org/www/articles/frustumcorrect/frustumcorrect.htm
	bool IsBoxVisible(const glm::vec3& minp, const glm::vec3& maxp) const;

private:
	enum Planes {
		Left = 0,
			Right,
			Bottom,
			Top,
			Near,
			Far,
			Count,
			Combinations = Count * (Count - 1) / 2
	};

	template < Planes i, Planes j >
		struct ij2k {
			enum {
				k = i * (9 - i) / 2 + j - 1
			};
		};

	template < Planes a, Planes b, Planes c >
		glm::vec3 intersection(const glm::vec3 * crosses) const;

	glm::vec4 m_planes[Count];
	glm::vec3 m_points[8];
};

#endif