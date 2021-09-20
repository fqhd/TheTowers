#version 330 core

layout (location = 0) in vec3 in_position;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 blockPosition;

void main(){
	gl_Position = projection * view * vec4(blockPosition + in_position, 1.0);
}
