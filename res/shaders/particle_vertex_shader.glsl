#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in uint textureIndex;

out float pass_textureIndex;

uniform mat4 projection;
uniform mat4 view;

const float POINT_SIZE = 50.0f;

void main(){
	gl_Position = projection * view * vec4(position, 1.0);
	gl_PointSize = POINT_SIZE / gl_Position.w;
	pass_textureIndex = float(textureIndex);
}
