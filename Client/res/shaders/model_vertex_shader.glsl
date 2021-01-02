#version 330 core

//Ins
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

//Outs
out vec3 pass_normal;

//Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float density;
uniform float gradient;

//Constants

void main(){

     gl_Position = projection * view * model * vec4(in_position, 1.0);

     pass_normal = (model * vec4(in_normal, 0.0)).xyz;



}
