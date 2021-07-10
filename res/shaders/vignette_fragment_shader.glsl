#version 330 core

in vec2 pass_uv;

out vec4 out_color;

uniform sampler2D ourTexture;

void main(){
    vec3 textureColor = texture(ourTexture, pass_uv).rgb;
    out_color = vec4(textureColor, 1.0);
}
