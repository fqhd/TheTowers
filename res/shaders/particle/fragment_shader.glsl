#version 330 core

in float pass_textureIndex;

out vec4 out_color;

uniform sampler2DArray ourTexture;

void main(){
	out_color = texture(ourTexture, vec3(gl_PointCoord * 0.75 + 0.25, pass_textureIndex));
}
