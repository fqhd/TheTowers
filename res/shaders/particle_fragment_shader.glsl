#version 330 core

in vec3 pass_uv;

out vec4 out_color;

uniform sampler2DArray ourTexture;

void main(){
	out_color = texture(ourTexture, pass_uv);
}
