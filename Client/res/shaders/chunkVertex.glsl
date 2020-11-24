#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 pass_color;

uniform mat4 matrix;

void main(){


	gl_Position = matrix * vec4(position, 1.0);

	pass_color = color;

}
