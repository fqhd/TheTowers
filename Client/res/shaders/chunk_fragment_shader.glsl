#version 410 core

//Ins
in vec3 pass_color;
in float visibility;

//Outs
out vec4 out_color;

//Uniforms
const vec3 skyColor = vec3(0.5444, 0.62, 0.69);


void main() {

     out_color = vec4(mix(skyColor, pass_color, visibility), 1.0);


}
