#version 330 core

// Ins
layout (location = 0) in uint vertexData;

// Outs
out float pass_AO;
out vec3 textureData;

//Uniforms
uniform mat4 view;
uniform mat4 projection;
uniform vec3 chunkPosition;
uniform vec3 cameraPosition;

// Constants
vec2 texCoords[4] = vec2[4](
    vec2(0.0f, 1.0f),
    vec2(0.0f, 0.0f),
    vec2(1.0f, 0.0f),
    vec2(1.0f, 1.0f)
);

float calcVisibility(float d, float density, float gradient){
	return clamp(exp(-pow((d*density), gradient)), 0.0, 1.0);
}

float calcAO(float ao, float d) {
	return ao + (1.0 - ao) * (1.0 - calcVisibility(d, 0.004, 1.5));
}

float map(float value, float min1, float max1, float min2, float max2) {
	return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main(){

	// Extracting information position
	float x = float(vertexData & 0x3Fu);
	float y = float((vertexData & 0xFC0u) >> 6u);
	float z = float((vertexData & 0x3F000u) >> 12u);
	float basicLight = float((vertexData & 0x1C0000u) >> 18u);
	uint coordIndex = (vertexData & 0x600000u) >> 21u;
	uint arrayIndex = (vertexData & 0xFF800000u) >> 23u;

	vec3 worldPosition = vec3(x, y, z) + chunkPosition;
	gl_Position = projection * view * vec4(worldPosition, 1.0);
	textureData = vec3(texCoords[coordIndex], arrayIndex);

	// Calculating AO and Fog
	float d = distance(worldPosition, cameraPosition);
	pass_AO = map(basicLight, 0, 3, 0.2, 1.0);
	pass_AO = calcAO(pass_AO, d);

}

