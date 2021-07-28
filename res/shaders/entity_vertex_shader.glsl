#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec2 pass_uv;
out vec3 pass_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	gl_Position = projection * view * model * vec4(position, 1.0);
	pass_normal = (model * vec4(normal, 1.0)).xyz;
	pass_uv = uv;
}