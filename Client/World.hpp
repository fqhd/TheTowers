#pragma once
#include "Chunk.hpp"
#include "Camera.hpp"
#include "Constants.hpp"
#include "ChunkShader.hpp"
#include <glm/gtc/noise.hpp>
#include <cstdint>

class World{
public:


     void init(uint8_t* d);
     void render(Camera& camera, const std::vector<vec3>& colors, float range);
     void destroy();

     uint8_t getBlock(int x, int y, int z);
     void setBlock(int x, int y, int z, uint8_t block);


     uint8_t* data = nullptr;

private:

     void generateMesh(const std::vector<vec3>& colors, Chunk& chunk);
     Chunk* getChunk(int x, int y, int z);

     void addTopFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addBottomFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addRightFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addLeftFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addFrontFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addBackFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);

     std::vector<Vertex> m_vertices;

     Chunk chunks[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE];
     ChunkShader m_chunkShader;


};
