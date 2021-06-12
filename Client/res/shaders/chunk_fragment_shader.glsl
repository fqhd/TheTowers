#version 410 core


// Ins
in float pass_AO;
in float visibility;
in vec3 textureData;

// Outs
out vec4 out_color;

// Uniforms
uniform sampler2DArray textureMap;

// Constants
const vec3 skyColor = vec3(0.5444, 0.62, 0.69);

void main() {

	out_color = texture(textureMap, textureData);
	out_color = vec4(out_color.rgb * pass_AO, 1.0);
	out_color = vec4(mix(skyColor, out_color.rgb, visibility), 1.0);

}
