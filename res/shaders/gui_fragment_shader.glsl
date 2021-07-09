#version 330 core

in vec4 pass_color;
in vec3 pass_textureData;

out vec4 out_color;

uniform sampler2DArray textureMap;

void main() {
    out_color = pass_color * texture(textureMap, pass_textureData);
}
