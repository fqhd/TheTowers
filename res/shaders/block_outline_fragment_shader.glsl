#version 330 core

out vec4 out_color;

uniform bool legacyOutline;

void main(){
	if(legacyOutline == true){
		out_color = vec4(0.0, 0.0, 0.0, 1.0);
	}else{
		out_color = vec4(1.0, 1.0, 1.0, 0.5);
	}
}
