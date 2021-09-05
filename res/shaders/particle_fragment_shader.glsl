#version 330 core

out vec4 out_color;

uniform sampler2DArray ourTexture;

void main(){
	// out_color = texture(ourTexture, pass_uv);
	out_color = vec4(1, 0, 0, 1);
}
