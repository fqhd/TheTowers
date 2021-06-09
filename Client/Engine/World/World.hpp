#ifndef WORLD_H
#define WORLD_H
#include "../World/Chunk.hpp"
#include "../Libs/Frustum.hpp"
#include "../Utils/Camera.hpp"
#include "../Utils/ChunkShader.hpp"
#include "../../Settings.hpp"
#include <glm/gtc/noise.hpp>
#include <cstdint>

struct World {

	void init(uint8_t* d);
	void render(Settings& settings, Camera& camera, const std::vector<vec3>& colors);
	void destroy();
	uint8_t getBlock(int x, int y, int z);
	void setBlock(int x, int y, int z, uint8_t block);
	void addBlock(Chunk* _c, int _x, int _y, int _z, const vec3& _color);

	void generateMesh(const std::vector<vec3>& colors, Chunk* chunk);
	Chunk* getChunk(int x, int y, int z);

	//Mesh generation functions
	void addTopFace(Chunk* c, int x, int y, int z, const vec3& color);
	void addBottomFace(Chunk* c, int x, int y, int z, const vec3& color);
	void addRightFace(Chunk* c, int x, int y, int z, const vec3& color);
	void addLeftFace(Chunk* c, int x, int y, int z, const vec3& color);
	void addFrontFace(Chunk* c, int x, int y, int z, const vec3& color);
	void addBackFace(Chunk* c, int x, int y, int z, const vec3& color);

	//We keep vertices so we dont have to reallocate memory every time we want to generate a chunk
	std::vector<Vertex> vertices;

	Chunk* chunks = nullptr;
	ChunkShader shader;
	uint8_t* data = nullptr;


};


#endif
