#include "Mat4.hpp"

namespace math {

	// mat4 struct
	mat4::mat4(float val) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {m[i][j] = val;}
		}
	}
}