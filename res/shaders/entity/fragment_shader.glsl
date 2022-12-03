#version 330 core

in vec3 pass_lightDirection;
in vec3 pass_normal;

out vec4 out_color;

uniform bool isBlueTeam;

void main(){
	float brightness = clamp(dot(-normalize(pass_lightDirection), pass_normal), 0.2, 1.0);

	vec3 color;
	if(isBlueTeam){
		color = vec3(0.0, 0.0, 1.0);
	}else{
		color = vec3(1.0, 0.0, 0.0);
	}

	out_color = vec4(color * brightness, 1);
}