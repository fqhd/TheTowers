#version 130

in vec2 vertexPosition;
in vec4 vertexColor;

out vec4 pass_color;

uniform mat4 matrix;

void main() {

    gl_Position = matrix * vec4(vertexPosition, 0.0, 1.0);
    
    pass_color = vertexColor;

}