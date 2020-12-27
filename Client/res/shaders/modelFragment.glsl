#version 410 core

uniform vec3 color;

out vec4 c;

void main(){

	c = vec4(color, 1.0);

}
