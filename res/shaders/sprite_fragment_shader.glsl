#version 330 core

in vec4 pass_color;
in vec2 pass_uv;

out vec4 out_color;

uniform bool isFont;
uniform sampler2D ourTexture;

void main() {
	if(isFont){
	    float a = texture(ourTexture, pass_uv).r;
		out_color = vec4(pass_color.rgb, pass_color.a * a);
	}else{
	    out_color = pass_color * texture(ourTexture, vec2(pass_uv.x, 1.0 - pass_uv.y));
	}
}
