#pragma once
#include "Chunk.hpp"
#include "Camera.hpp"
#include "Constants.hpp"
#include "ChunkShader.hpp"
#include <glm/gtc/noise.hpp>

class World{
public:


    void init();
    void render(Camera& camera, const std::vector<vec3>& colors);
    void destroy();

    char getBlock(int x, int y, int z);
	void setBlock(int x, int y, int z, char block);

private:

     void generateWorld();
     void generateMesh(const std::vector<vec3>& colors, Chunk& chunk);
     Chunk* getChunk(int x, int z);

     void addTopFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addBottomFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addRightFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addLeftFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addFrontFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addBackFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);

     std::vector<Vertex> m_vertices;

     char* m_data = nullptr;
     Chunk chunks[WORLD_SIZE][WORLD_SIZE];
     ChunkShader m_chunkShader;


};
