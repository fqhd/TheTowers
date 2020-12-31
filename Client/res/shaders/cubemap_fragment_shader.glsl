#version 410 core

//Ins
in vec3 textureCoords;

//Outs
out vec4 out_color;

//Uniforms
uniform samplerCube skybox;

//Constants
const float upperLimit = 0.2;
const float lowerLimit = 0.0;
const vec3 skyColor = vec3(0.5444, 0.62, 0.69);

void main(){

    out_color = texture(skybox, textureCoords);

    float factor = (textureCoords.y - lowerLimit) / (upperLimit - lowerLimit);
    factor = clamp(factor, 0.0, 1.0);
    out_color = mix(vec4(skyColor, 1.0), out_color, factor);

}
