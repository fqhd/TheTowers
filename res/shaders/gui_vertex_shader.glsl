#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 textureInfo;

out vec4 pass_color;
out vec3 pass_textureData;

uniform mat4 matrix;

vec2 texCoords[4] = vec2[4](
    vec2(0.0f, 1.0f),
    vec2(0.0f, 0.0f),
    vec2(1.0f, 0.0f),
    vec2(1.0f, 1.0f)
);

void main() {
    gl_Position = matrix * vec4(position, 0.0, 1.0);

    pass_color = color;
    pass_textureData = vec3(texCoords[uint(textureInfo.x)], uint(textureInfo.y));
}
