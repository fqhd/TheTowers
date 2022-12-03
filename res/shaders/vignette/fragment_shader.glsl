#version 330 core

in vec2 pass_coords;

out vec4 out_color;

void main(){
	float factor = abs(pass_coords.x) + abs(pass_coords.y);
	factor = factor / 2.0;
	factor = factor * factor;
	factor *= 0.8;
	out_color = vec4(0, 0, 0, factor);
}
