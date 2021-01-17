#ifndef WORLD_H
#define WORLD_H
#include "Chunk.hpp"
#include "Frustum.hpp"
#include "Camera.hpp"
#include "ChunkShader.hpp"
#include "Settings.hpp"
#include <glm/gtc/noise.hpp>
#include <cstdint>


class World{
public:

     void init(uint8_t* d);
     void update(const std::vector<vec3>& colors, const glm::vec3& previousCameraPosition, const glm::vec3& currentCameraPosition);
     void render(Settings& settings, Camera& camera, const std::vector<vec3>& colors);
     void destroy();
	void updateChunks(const std::vector<vec3>& colors);
     uint8_t getBlock(int x, int y, int z);
     void setBlock(int x, int y, int z, uint8_t block);


private:

     void generateMesh(const std::vector<vec3>& colors, Chunk* chunk);
     Chunk* getChunk(int x, int y, int z);

     //World movement functions
     void moveFront();
     void moveBack();
     void moveRight();
     void moveLeft();

     //Mesh generation functions
     void addTopFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addBottomFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addRightFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addLeftFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addFrontFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);
     void addBackFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices);

     //We keep vertices so we dont have to reallocate memory every time we want to generate a chunk

     Chunk* m_chunks = nullptr;
     ChunkShader m_shader;
     unsigned int m_chunkOffsetX = 0;
     unsigned int m_chunkOffsetZ = 0;
     uint8_t* m_data = nullptr;




};


#endif
