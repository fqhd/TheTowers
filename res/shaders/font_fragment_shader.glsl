#version 330 core

//Ins
in vec2 pass_uv;

//Outs
out vec4 out_color;

//Uniforms
uniform sampler2D ourTexture;
uniform vec4 color;

//Constants


void main() {
    float red = texture(ourTexture, pass_uv).r;

	out_color = vec4(color.rgb, red * color.a);
}
