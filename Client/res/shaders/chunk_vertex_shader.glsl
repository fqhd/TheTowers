#version 410 core

//Ins
layout (location = 0) in uint vertexData;

//Outs

//Uniforms
uniform mat4 view;
uniform mat4 projection;
uniform vec3 chunkPosition;

void main(){

	// Extracting information position
	float x = float(vertexData & 0x3Fu);
	float y = float((vertexData & 0xFC0u) >> 6u);
	float z = float((vertexData & 0x3F000u) >> 12u);
	float basicLight = float((vertexData & 0x1C0000u) >> 18u) / 3.0f;
	uint coordIndex = (vertexData & 0x600000u) >> 21u;
	uint arrayIndex = (vertexData & 0xFF800000u) >> 23u;


	vec3 worldPosition = vec3(x, y, z) + chunkPosition;

	vec4 positionRelativeToCamera = view * vec4(worldPosition, 1.0);

	gl_Position = projection * positionRelativeToCamera;


}
