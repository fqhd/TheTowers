#ifndef WORLD_H
#define WORLD_H
#include "Chunk.hpp"
#include "Camera.hpp"
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

     void generateMesh(const std::vector<vec3>& colors, Chunk* chunk);
     Chunk* getChunk(int x, int y, int z);
     void swapChunks(Chunk* a, Chunk* b);

     //Moving functions
     void moveFront();
     void moveRight();
     void moveLeft();
     void moveBack();

     //Mesh generation functions
     void addTopFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addBottomFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addRightFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addLeftFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addFrontFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addBackFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);

     //We keep vertices so we dont have to reallocate memory every time we want to generate a chunk
     std::vector<Vertex> m_vertices;

     Chunk* m_chunks;
     ChunkShader m_chunkShader;


};


#endif
