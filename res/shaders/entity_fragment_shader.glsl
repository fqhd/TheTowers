#version 330 core

out vec4 out_color;

uniform bool team;

void main(){
	if(team){
		out_color = vec4(0, 0, 1, 1);
	}else{
		out_color = vec4(1, 0, 0, 1);
	}
}