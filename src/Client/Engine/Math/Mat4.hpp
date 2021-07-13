#pragma once

namespace math {
	// matrices
	template<typename T>
	struct base_mat4 {
		T m[4][4];
		base_mat4() {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					m[i][j] = 0.0f;
				}
			}
		}
		// inits all values to val
		base_mat4(T val) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					m[i][j] = val;
				}
			}
		}

		void setIdentity(){
			m[0][0] = (T)1.0f;
			m[1][1] = (T)1.0f;
			m[2][2] = (T)1.0f;
			m[3][3] = (T)1.0f;
		}


	};

	typedef base_mat4<float> mat4;
}
