#version 330 core

//Ins
in vec3 pass_normal;

//Outs
out vec4 out_color;

//Uniforms
uniform bool isBlueTeam;
uniform vec3 lightDir;

//Constants

void main(){
    vec3 color;
    if(isBlueTeam){
        color = vec3(0, 0, 1);
    }else{
        color = vec3(1, 0, 0);
    }
    out_color = vec4(color * clamp(dot(normalize(-lightDir), pass_normal), 0.2, 1.0), 1.0);
}
