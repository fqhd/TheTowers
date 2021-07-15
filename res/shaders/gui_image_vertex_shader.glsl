#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

// Outs
out vec2 pass_uv;

// Uniforms
uniform vec2 positionOffset;
uniform mat4 matrix;


void main(){
    gl_Position = matrix * vec4(position + positionOffset, 0.0, 1.0);
	pass_uv = uv;
}
