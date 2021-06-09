#version 410 core

//Ins
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

//Outs
out vec3 pass_color;
out float visibility;

//Uniforms
uniform mat4 view;
uniform mat4 projection;
uniform float density;
uniform float gradient;
uniform vec3 chunkPosition;

void main(){


	vec3 worldPosition = chunkPosition + position;
	vec4 positionRelativeToCamera = view * vec4(worldPosition, 1.0);

	gl_Position = projection * positionRelativeToCamera;
	pass_color = color;

	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance * density), gradient));
	visibility = clamp(visibility, 0.0, 1.0);

}
