#ifndef WORLD_H
#define WORLD_H
#include "../World/Chunk.hpp"
#include "../Libs/Frustum.hpp"
#include "../Utils/Camera.hpp"
#include "../Utils/ChunkShader.hpp"
#include "../Utils/TextureArray.hpp"
#include "../../NetworkManager.hpp"
#include <glm/gtc/noise.hpp>
#include <cstdint>

class NetworkManager;

const unsigned int WORLD_WIDTH = 8;
const unsigned int WORLD_HEIGHT = 4;

struct BlockTexture {
	BlockTexture(uint16_t _t){
		top = _t;
		side = _t;
		bot = _t;
	}
	BlockTexture(uint16_t _top, uint16_t _side, uint16_t _bot){
		top = _top;
		side = _side;
		bot = _bot;
	}
	uint16_t top = 0;
	uint16_t side = 0;
	uint16_t bot = 0;
};

class World {
public:

	friend class NetworkManager;

	void init(NetworkManager& _manager);
	void render(Camera& _camera);
	void destroy();
	uint8_t getBlock(int x, int y, int z);
	void setBlock(int x, int y, int z, uint8_t block);


private:

	// Utility functions
	void generateMesh(Chunk* chunk);
	GLuint packData(uint8_t x, uint8_t y, uint8_t z, uint8_t lightLevel, uint8_t textureCoordinateIndex, uint16_t textureArrayIndex);
	void addBlock(Chunk* _c, int _x, int _y, int _z, uint8_t _blockType);
	BlockTexture getTextureFromBlockID(uint8_t _blockID);
	bool isBlockInLocalWorld(int _x, int _y, int _z);

	// Mesh generation functions
	void addTopFace(Chunk* _c, uint8_t _x, uint8_t _y, uint8_t _z, uint16_t _textureLayer);
	void addBottomFace(Chunk* _c, uint8_t _x, uint8_t _y, uint8_t _z, uint16_t _textureLayer);
	void addRightFace(Chunk* _c, uint8_t _x, uint8_t _y, uint8_t _z, uint16_t _textureLayer);
	void addLeftFace(Chunk* _c, uint8_t _x, uint8_t _y, uint8_t _z, uint16_t _textureLayer);
	void addFrontFace(Chunk* _c, uint8_t _x, uint8_t _y, uint8_t _z, uint16_t _textureLayer);
	void addBackFace(Chunk* _c, uint8_t _x, uint8_t _y, uint8_t _z, uint16_t _textureLayer);
	Chunk* getChunk(int x, int y, int z);

	//We keep vertices so we dont have to reallocate memory every time we want to generate a chunk
	std::vector<GLuint> vertices;

	Chunk* chunks = nullptr;
	ChunkShader shader;
	uint8_t* data = nullptr;
	TextureArray texturePack;
};


#endif
