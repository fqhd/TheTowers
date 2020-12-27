#version 410 core

in vec3 textureCoords;

out vec4 color;

uniform samplerCube skybox;

void main(){ 
    color = texture(skybox, textureCoords);
}
