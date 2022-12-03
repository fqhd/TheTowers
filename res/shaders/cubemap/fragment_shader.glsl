#version 330 core

//Ins
in vec3 textureCoords;

//Outs
out vec4 out_color;

//Constants
const float upperLimit = 0.2;
const float lowerLimit = 0.0;
const vec3 topColor = vec3(132.0/255.0, 174.0/255.0, 255.0/255.0);
const vec3 bottomColor = vec3(178.0/255.0, 206.0/255.0, 254.0/255.0);

void main(){
    float blendFactor = clamp((normalize(textureCoords).y - lowerLimit) / (upperLimit - lowerLimit), 0.0, 1.0);
    out_color = vec4(mix(bottomColor, topColor, blendFactor), 1.0);
}
