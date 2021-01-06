#version 330 core

//Ins
layout (location = 0) in vec3 in_position;

//Outs

//Uniforms
uniform mat4 projection;
uniform mat4 view;
uniform vec3 blockPosition;

//Constants


void main(){

     gl_Position = projection * view * vec4(blockPosition + in_position, 1.0);

}
