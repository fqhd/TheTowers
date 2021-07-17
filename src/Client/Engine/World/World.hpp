#pragma once

#include "../World/Chunk.hpp"
#include "../Utils/Camera.hpp"
#include "../Utils/ChunkShader.hpp"
#include "../Utils/TextureArray.hpp"
#include "../../NetworkManager.hpp"
#include "../../Config.hpp"
#include <cstdint>

class NetworkManager;

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

	void init(NetworkManager& _manager, Config& _c, TextureArray* _textureArray);
	void render(Camera& _camera);
	uint8_t getBlock(int _x, int _y, int _z);
	void setBlock(int _x, int _y, int _z, uint8_t _block);
	void destroy();
	Config& getConfig();

private:

	// Utility functions
	void generateMesh(Chunk* chunk);
	GLuint packData(uint8_t x, uint8_t y, uint8_t z, uint8_t lightLevel, uint8_t textureCoordinateIndex, uint16_t textureArrayIndex);
	void addBlock(Chunk* _c, int _x, int _y, int _z, uint8_t _blockType);
	BlockTexture getTextureFromBlockID(uint8_t _blockID);
	bool isBlockInLocalWorld(int _x, int _y, int _z);
	void loadBlockTexturesFromFile();

	// Mesh generation functions
	void addTopFace(Chunk* _c, uint8_t _x, uint8_t _y, uint8_t _z, uint16_t _textureLayer);
	void addBottomFace(Chunk* _c, uint8_t _x, uint8_t _y, uint8_t _z, uint16_t _textureLayer);
	void addRightFace(Chunk* _c, uint8_t _x, uint8_t _y, uint8_t _z, uint16_t _textureLayer);
	void addLeftFace(Chunk* _c, uint8_t _x, uint8_t _y, uint8_t _z, uint16_t _textureLayer);
	void addFrontFace(Chunk* _c, uint8_t _x, uint8_t _y, uint8_t _z, uint16_t _textureLayer);
	void addBackFace(Chunk* _c, uint8_t _x, uint8_t _y, uint8_t _z, uint16_t _textureLayer);
	Chunk* getChunk(int x, int y, int z);

	//We keep vertices so we dont have to reallocate memory every time we want to generate a chunk
	std::vector<GLuint> m_vertices;
	std::vector<BlockTexture> m_blockTextures;

	TextureArray* m_textureArray = nullptr;
	Chunk* m_chunks = nullptr;
	ChunkShader m_shader;
	uint8_t* m_data = nullptr;
	Config m_config;

};
