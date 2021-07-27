#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in mat4 model;
layout (location = 5) in vec4 uv;

out vec2 pass_uv;

uniform mat4 projection;
uniform mat4 view;

void main(){
	gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
	switch(gl_VertexID){
		case 0:
			pass_uv.x = uv.x;
			pass_uv.y = uv.y;
		break;
		case 1:
			pass_uv.x = uv.x;
			pass_uv.y = uv.y + uv.w;
		break;
		case 2:
			pass_uv.x = uv.x + uv.z;
			pass_uv.y = uv.y + uv.w;
		break;
		case 3:
			pass_uv.x = uv.x;
			pass_uv.y = uv.y;
		break;
		case 4:
			pass_uv.x = uv.x + uv.z;
			pass_uv.y = uv.y + uv.w;
		break;
		case 5:
			pass_uv.x = uv.x + uv.z;
			pass_uv.y = uv.y;
		break;
	}
}
