#version 330 core

//Ins
layout (location = 0) in vec2 in_position;
layout (location = 1) in vec2 in_uv;

//Outs
out vec2 pass_uv;

//Uniforms
uniform mat4 matrix;
uniform vec2 position;

//Constants

void main() {

    gl_Position = matrix * vec4(in_position + position, 0.0, 1.0);
    pass_uv = in_uv;

}
