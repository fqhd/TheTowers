#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in mat4 model;
layout (location = 5) in uint uv;

out vec3 pass_uv;

uniform mat4 projection;
uniform mat4 view;

void main(){
	gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
	pass_uv = vec3(position, uv);
}
