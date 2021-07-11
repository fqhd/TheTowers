#pragma once

#include <array>
#include <cstdlib>

namespace math {

    typedef float f32;
    typedef double f64;
    

    // vectors

    template<typename T, size_t len>
    struct vec{
        vec<T, len>(T val);
        T v[len];
    };

    typedef vec<f32, 2> vec2;


    // matrices

    struct mat4
	{	
        // inits all values to param f
		mat4(int n);
		f32 m[4][4];
	};


    // functions
    mat4 perspective(f32 fovy, f32 aspect, f32 zNear, f32 zFar);

};