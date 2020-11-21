#version 330 core

in vec3 textureCoords;

uniform samplerCube skybox;

void main(){ 
    gl_FragColor = texture(skybox, textureCoords);
}