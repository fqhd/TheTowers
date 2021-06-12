#version 410 core


//Ins
in float pass_basicLight;

//Outs
out vec4 out_color;


void main() {

	out_color = vec4(1 * pass_basicLight, 0, 0, 1);


}
