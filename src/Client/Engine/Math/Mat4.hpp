#pragma once

namespace math {
	  // matrices
	struct mat4 {
		mat4();
		mat4(float n); // inits all values to param f
		float m[4][4];

		void setIdentity();

	};
}
