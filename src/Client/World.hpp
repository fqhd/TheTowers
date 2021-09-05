#pragma once

#include "Chunk.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "TextureArray.hpp"
#include "Config.hpp"
#include "BlockTextureHandler.hpp"
#include <cstdint>

class World {
public:

	void init(TextureArray* _array, Config* _c, BlockTextureHandler* _textureHandler);
	void render(Camera& _camera);
	uint8_t getBlock(int _x, int _y, int _z);
	void setBlock(int _x, int _y, int _z, uint8_t _block);
	void destroy();

	void loadWorldFromFile(const std::string& path);
	void saveWorldToFile(const std::string& path);

private:

	// Utility functions
	void generateMesh(Chunk* chunk);
	GLuint packData(uint8_t x, uint8_t y, uint8_t z, uint8_t lightLevel, uint8_t textureCoordinateIndex, uint16_t textureArrayIndex);
	void addBlock(Chunk* _c, int _x, int _y, int _z, uint8_t _blockType);
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
	std::vector<GLuint> m_vertices;
	Shader m_shader;
	unsigned int m_data_length = 0;

	TextureArray* m_textureArray = nullptr;
	BlockTextureHandler* m_blockTextureHandler = nullptr;
	Chunk* m_chunks = nullptr;
	Config* m_config = nullptr;
	uint8_t* m_data = nullptr;


};
