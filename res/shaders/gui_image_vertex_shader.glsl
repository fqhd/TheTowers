#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in uint uv;

// Outs
out vec2 pass_uv;

// Uniforms
uniform vec2 positionOffset;
uniform mat4 matrix;

// Constants
vec2 texCoords[4] = vec2[4](
    vec2(0.0f, 0.0f),
    vec2(0.0f, 1.0f),
    vec2(1.0f, 1.0f),
    vec2(1.0f, 0.0f)
);


void main(){
    gl_Position = matrix * vec4(position + positionOffset, 0.0, 1.0);
	pass_uv.x = uv;
	pass_uv.y = uv;

}
