#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in uint uv;

uniform mat4 projection;
uniform mat4 view;

void main(){
	gl_PointSize = 10;
	gl_Position = projection * view * vec4(position, 1.0);
}
