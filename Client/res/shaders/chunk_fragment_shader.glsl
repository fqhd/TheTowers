#version 410 core


// Ins
in float pass_basicLight;
in vec3 textureData;

// Outs
out vec4 out_color;

// Uniforms
uniform sampler2DArray textureMap;

void main() {

	out_color = texture(textureMap, textureData);
	out_color = vec4(out_color.rgb * pass_basicLight, 1.0);

}
