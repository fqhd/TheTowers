#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;

out vec4 pass_color;
out vec3 pass_uv;

uniform mat4 matrix;

void main() {
    gl_Position = matrix * vec4(position, 1.0);

    pass_color = color;
	pass_uv = uv;
}
