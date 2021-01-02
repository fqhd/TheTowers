#version 330 core

//Ins
in vec3 pass_normal;

//Outs
out vec4 out_color;

//Uniforms
uniform vec3 color;

//Constants

void main(){

     out_color = vec4(color * clamp(dot(vec3(0, 0, -1), pass_normal), 0.2, 1.0), 1.0);

}
