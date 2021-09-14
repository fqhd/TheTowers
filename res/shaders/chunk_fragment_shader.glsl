#version 330 core

// Ins
in float pass_AO;
in vec3 textureData;

// Outs
out vec4 out_color;

// Uniforms
uniform sampler2DArray textureMap;

void main() {
	out_color = texture(textureMap, textureData);
	if(out_color.a < 0.5) discard;
	out_color = vec4(out_color.rgb * pass_AO, 1.0);
}
