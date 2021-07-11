#pragma once

#include <array>
#include <cstdlib>

namespace math {

    typedef float f32;
    typedef double f64;

    // vectors

    
    struct vec2{
        vec2(f32 val);
        vec2();
        f32 v[2];
    };

    struct vec3{
        vec3(f32 val);
        vec3();
        f32 v[3];
    };

    struct vec4 {
        vec4(f32 val);
        vec4();
        f32 v[4];
    };

    // matrices
    struct mat4
	{	
        // inits all values to param f
		mat4(float n);
		float m[4][4]; 
	};


    // functions
    mat4 perspective(f32 fovy, f32 aspect, f32 zNear, f32 zFar);

};