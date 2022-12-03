#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 pass_lightDirection;
out vec3 pass_normal;

uniform vec3 camPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	vec4 worldPosition = model * vec4(position, 1.0);
	gl_Position = projection * view * worldPosition;
	pass_normal = (model * vec4(normal, 0.0)).xyz;
	pass_lightDirection = worldPosition.xyz - camPos;
}