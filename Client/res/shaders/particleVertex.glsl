#version 410 core

layout (location = 0) in vec2 position;
layout (location = 1) in mat4 view;
layout (location = 5) in vec3 color;

out vec3 pass_color;

uniform mat4 projection;

void main(){
     pass_color = color;
     gl_Position = projection * view * vec4(position, 0.0, 1.0);
}
