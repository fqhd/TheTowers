#version 330 core

in vec2 pass_uv;

out vec4 out_color;

uniform sampler2D ourTexture;

void main(){
	out_color = texture(ourTexture, vec2(pass_uv.x, 1.0 - pass_uv.y));
}
