#include "World.hpp"
#include <iostream>


void World::init(NetworkManager& _manager, Config& _c, TextureArray* _textureArray){
	m_textureArray = _textureArray;
	m_config = _c;
	unsigned int ww = m_config.getWorldWidth();
	unsigned int wl = m_config.getWorldLength();
	unsigned int wh = m_config.getWorldHeight();
	unsigned int cw = m_config.getChunkWidth();

	m_data = static_cast<uint8_t*>(malloc(ww * wl * wh * cw * cw * cw));
	_manager.downloadWorld(m_data);

	// Populating blockTextures array
	loadBlockTexturesFromFile();

	// Initializing the m_chunks
	m_chunks = new Chunk[ww * wl * wh];
	for(unsigned int y = 0; y < wh; y++){
		for(unsigned int z = 0; z < wl; z++){
			for(unsigned int x = 0; x < ww; x++){
				getChunk(x, y, z)->init(x * cw, y * cw, z * cw);
			}
		}
	}

	// Initializing the m_shader
	m_shader.init();
}

GLuint World::packData(uint8_t x, uint8_t y, uint8_t z, uint8_t lightLevel, uint8_t textureCoordinateIndex, uint16_t textureArrayIndex) {
	GLuint vertex = x | y << 6 | z << 12 | lightLevel << 18 | textureCoordinateIndex << 21 | textureArrayIndex << 23;
	return vertex;
}

void World::render(Camera& _camera){
	m_shader.bind();

	m_textureArray->bind();

	m_shader.loadProjectionMatrix(_camera.getProjectionMatrix());
	m_shader.loadViewMatrix(_camera.getViewMatrix());
	m_shader.loadCameraPosition(_camera.getPosition());

	unsigned int ww = m_config.getWorldWidth();
	unsigned int wl = m_config.getWorldLength();
	unsigned int wh = m_config.getWorldHeight();

	for(unsigned int y = 0; y < wh; y++){
		for(unsigned int z = 0; z < wl; z++){
			for(unsigned int x = 0; x < ww; x++){
				Chunk* c = getChunk(x, y, z);

				if(c->needsMeshUpdate){ // Generate mesh if chunk needs mesh update
					generateMesh(c);
					c->needsMeshUpdate = false;
				}

				if(c->getNumVertices()){ // Render only if chunk has vertices
					m_shader.loadChunkPosition(c->x, c->y, c->z);
					c->render();
				}

			}
		}
	}

	m_textureArray->unbind();

	m_shader.unbind();
}

void World::destroy(){
	unsigned int ww = m_config.getWorldWidth();
	unsigned int wl = m_config.getWorldLength();
	unsigned int wh = m_config.getWorldHeight();

	for(unsigned int y = 0; y < wh; y++){
		for(unsigned int z = 0; z < wl; z++){
			for(unsigned int x = 0; x < ww; x++){
				getChunk(x, y, z)->destroy();
			}
		}
	}
	m_shader.destroy();
	delete[] m_chunks;
	free(m_data);
}

void World::generateMesh(Chunk* _chunk){
	sf::Clock c;
	m_vertices.resize(0);
	unsigned int cw = m_config.getChunkWidth();

	for(unsigned int y = 0; y < cw; y++){
		for(unsigned int z = 0; z < cw; z++){
			for(unsigned int x = 0; x < cw; x++){
				//May be better to get the surrounding blocks and then check against them rather than get the surrounding blocks every time. Because then, they will be stored in the cache rather than having to go look through the entire array of data for the surrounding blocks in ram which is farther away from the cpu
				uint8_t block = getBlock(_chunk->x + x, _chunk->y + y, _chunk->z + z);

				if(block){
					addBlock(_chunk, x, y, z, block);
				}
			}
		}
	}

	_chunk->pushData(m_vertices.data(), m_vertices.size());
}

bool World::isBlockInLocalWorld(int _x, int _y, int _z){
	unsigned int maxW = m_config.getWorldWidth() * m_config.getChunkWidth();
	unsigned int maxL = m_config.getWorldLength() * m_config.getChunkWidth();
	unsigned int maxH = m_config.getWorldHeight() * m_config.getChunkWidth();

	if(_x < 0 || _x >= maxW || _z < 0 || _z >= maxL || _y < 0 || _y >= maxH) return false;
	return true;
}

uint8_t World::getBlock(int _x, int _y, int _z){
	if(!isBlockInLocalWorld(_x, _y, _z)){
		return 0;
	}

	unsigned int maxW = m_config.getWorldWidth() * m_config.getChunkWidth();
	unsigned int maxL = m_config.getWorldLength() * m_config.getChunkWidth();

	return m_data[(_y * maxW * maxL) + (_z * maxW) + _x];
}

Config& World::getConfig() {
	return m_config;
}

void World::setBlock(int x, int y, int z, uint8_t block) {
	if(!isBlockInLocalWorld(x, y, z)){
		return;
	}

	unsigned int ww = m_config.getWorldWidth();
	unsigned int wl = m_config.getWorldLength();
	unsigned int wh = m_config.getWorldHeight();
	unsigned int cw = m_config.getChunkWidth();

	unsigned int maxW = ww * cw;
	unsigned int maxL = wl * cw;

	// Getting the chunk the block is in
	unsigned int posX = x / cw;
	unsigned int posY = y / cw;
	unsigned int posZ = z / cw;

	// Right now, we have the position of the chunk that the block has been placed in stored in posX, posY, and posZ
	// So we first of all, queue this chunk up for a mesh update
	getChunk(posX, posY, posZ)->needsMeshUpdate = true;

	// Setting the block based on chunk space coords
	m_data[(y * maxW * maxL) + (z * maxW) + x] = block;

	// Next, we check if the placed block has been placed on any edge
	// Update neighboring m_chunks if block is on the edge of the current chunk
	if(x % cw == 0){
		Chunk* chunk = getChunk((posX - 1) % ww, posY, posZ);
		if(chunk) chunk->needsMeshUpdate = true;
	}
	if((x + 1) % cw == 0){
		Chunk* chunk = getChunk((posX + 1) % ww, posY, posZ);
		if(chunk) chunk->needsMeshUpdate = true;
	}
	if(z % cw == 0){
		Chunk* chunk = getChunk(posX, posY, (posZ - 1) % wl);
		if(chunk) chunk->needsMeshUpdate = true;
	}
	if((z + 1) % cw == 0){
		Chunk* chunk = getChunk(posX, posY, (posZ + 1) % wl);
		if(chunk) chunk->needsMeshUpdate = true;
	}
	if(y % cw == 0){
		Chunk* chunk = getChunk(posX, (posY - 1) % wh, posZ);
		if(chunk) chunk->needsMeshUpdate = true;
	}
	if((y + 1) % cw == 0){
		Chunk* chunk = getChunk(posX, (posY + 1) % wh, posZ);
		if(chunk) chunk->needsMeshUpdate = true;
	}
}

void World::addBlock(Chunk* _c, int _x, int _y, int _z, uint8_t _blockType){
	BlockTexture blockTexture = getTextureFromBlockID(_blockType);

	addTopFace(_c, _x, _y, _z, blockTexture.top);
	addBottomFace(_c, _x, _y, _z, blockTexture.bot);
	addLeftFace(_c, _x, _y, _z, blockTexture.side);
	addRightFace(_c, _x, _y, _z, blockTexture.side);
	addFrontFace(_c, _x, _y, _z, blockTexture.side);
	addBackFace(_c, _x, _y, _z, blockTexture.side);
}

Chunk* World::getChunk(int _x, int _y, int _z) {
	unsigned int ww = m_config.getWorldWidth();
	unsigned int wl = m_config.getWorldLength();
	unsigned int wh = m_config.getWorldHeight();

	if(_y < 0 || _y >= wh || _x < 0 || _x >= ww || _z < 0 || _z >= wl){
		return nullptr;
	}
	return &m_chunks[(_y * ww * wl) + (_z * ww) + _x];
}

unsigned int calcAO(bool side1, bool side2, bool corner){
	if(side1 && side2){
		return 0;
	}
	return 3 - (side1 + side2 + corner);
}

void World::addTopFace(Chunk* c, uint8_t x, uint8_t y, uint8_t z, uint16_t _textureLayer){
	if(getBlock(c->x + x, c->y + y + 1, c->z + z)) return;

	unsigned int a00 = calcAO(getBlock(c->x + x, c->y + y + 1, c->z + z - 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z), getBlock(c->x + x - 1, c->y + y + 1, c->z + z - 1));
	unsigned int a01 = calcAO(getBlock(c->x + x - 1, c->y + y + 1, c->z + z), getBlock(c->x + x, c->y + y + 1, c->z + z + 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z + 1));
	unsigned int a11 = calcAO(getBlock(c->x + x, c->y + y + 1, c->z + z + 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z), getBlock(c->x + x + 1, c->y + y + 1, c->z + z + 1));
	unsigned int a10 = calcAO(getBlock(c->x + x, c->y + y + 1, c->z + z - 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z), getBlock(c->x + x + 1, c->y + y + 1, c->z + z - 1));

	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		m_vertices.emplace_back(packData(x, y + 1, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z + 1, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z, a10, 3, _textureLayer));
	} else {
		// Generate flipped quad
		m_vertices.emplace_back(packData(x + 1, y + 1, z, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z + 1, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z + 1, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
	}
}

void World::addBottomFace(Chunk* c, uint8_t x, uint8_t y, uint8_t z, uint16_t _textureLayer){
	if(getBlock(c->x + x, c->y + y - 1, c->z + z)) return;

	unsigned int a00 = calcAO(getBlock(c->x + x, c->y + y - 1, c->z + z - 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z), getBlock(c->x + x - 1, c->y + y - 1, c->z + z - 1));
	unsigned int a01 = calcAO(getBlock(c->x + x - 1, c->y + y - 1, c->z + z), getBlock(c->x + x, c->y + y - 1, c->z + z + 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z + 1));
	unsigned int a10 = calcAO(getBlock(c->x + x, c->y + y - 1, c->z + z - 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z), getBlock(c->x + x + 1, c->y + y - 1, c->z + z - 1));
	unsigned int a11 = calcAO(getBlock(c->x + x, c->y + y - 1, c->z + z + 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z), getBlock(c->x + x + 1, c->y + y - 1, c->z + z + 1));

	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		m_vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z + 1, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z + 1, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z + 1, a11, 2, _textureLayer));

	} else {
		// Generate flipped quad
		m_vertices.emplace_back(packData(x + 1, y, z, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z + 1, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z + 1, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z + 1, a01, 1, _textureLayer));
	}
}

void World::addRightFace(Chunk* c, uint8_t x, uint8_t y, uint8_t z, uint16_t _textureLayer){
	if(getBlock(c->x + x - 1, c->y + y, c->z + z)) return;

	unsigned int a00 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z - 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z), getBlock(c->x + x - 1, c->y + y - 1, c->z + z - 1));
	unsigned int a01 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z - 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z), getBlock(c->x + x - 1, c->y + y + 1, c->z + z - 1));
	unsigned int a10 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z + 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z), getBlock(c->x + x - 1, c->y + y - 1, c->z + z + 1));
	unsigned int a11 = calcAO(getBlock(c->x + x - 1, c->y + y + 1, c->z + z), getBlock(c->x + x - 1, c->y + y, c->z + z + 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z + 1));


	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		m_vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z + 1, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z + 1, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z + 1, a11, 2, _textureLayer));
	} else {
		// Generate flipped quad
		m_vertices.emplace_back(packData(x, y, z + 1, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z + 1, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z + 1, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z, a01, 1, _textureLayer));
	}
}

void World::addLeftFace(Chunk* c, uint8_t x, uint8_t  y, uint8_t z, uint16_t _textureLayer){
	if(getBlock(c->x + x + 1, c->y + y, c->z + z)) return;

	unsigned int a00 = calcAO(getBlock(c->x + x + 1, c->y + y, c->z + z - 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z), getBlock(c->x + x + 1, c->y + y - 1, c->z + z - 1));
	unsigned int a01 = calcAO(getBlock(c->x + x + 1, c->y + y, c->z + z - 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z), getBlock(c->x + x + 1, c->y + y + 1, c->z + z - 1));
	unsigned int a10 = calcAO(getBlock(c->x + x + 1, c->y + y, c->z + z + 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z), getBlock(c->x + x + 1, c->y + y - 1, c->z + z + 1));
	unsigned int a11 = calcAO(getBlock(c->x + x + 1, c->y + y + 1, c->z + z), getBlock(c->x + x + 1, c->y + y, c->z + z + 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z + 1));

	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		m_vertices.emplace_back(packData(x + 1, y, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z + 1, a10, 3, _textureLayer));
	} else {
		// Generate flipped quad
		m_vertices.emplace_back(packData(x + 1, y + 1, z, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z + 1, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z + 1, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z, a00, 0, _textureLayer));
	}
}

void World::addFrontFace(Chunk* c, uint8_t x, uint8_t y, uint8_t z, uint16_t _textureLayer){
	if(getBlock(c->x + x, c->y + y, c->z + z - 1)) return;

	unsigned int a00 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z - 1), getBlock(c->x + x, c->y + y - 1, c->z + z - 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z - 1));
	unsigned int a01 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z - 1), getBlock(c->x + x, c->y + y + 1, c->z + z - 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z - 1));
	unsigned int a10 = calcAO(getBlock(c->x + x, c->y + y - 1, c->z + z - 1), getBlock(c->x + x + 1, c->y + y, c->z + z - 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z - 1));
	unsigned int a11 = calcAO(getBlock(c->x + x, c->y + y + 1, c->z + z - 1), getBlock(c->x + x + 1, c->y + y, c->z + z - 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z - 1));

	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		m_vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z, a10, 3, _textureLayer));
	} else {
		// Generate flipped quad
		m_vertices.emplace_back(packData(x + 1, y, z, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z, a11, 2, _textureLayer));
	}
}

void World::addBackFace(Chunk* c, uint8_t x, uint8_t y, uint8_t z, uint16_t _textureLayer){
	if(getBlock(c->x + x, c->y + y, c->z + z + 1)) return;

	unsigned int a00 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z + 1), getBlock(c->x + x, c->y + y - 1, c->z + z + 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z + 1));
	unsigned int a01 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z + 1), getBlock(c->x + x, c->y + y + 1, c->z + z + 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z + 1));
	unsigned int a10 = calcAO(getBlock(c->x + x, c->y + y - 1, c->z + z + 1), getBlock(c->x + x + 1, c->y + y, c->z + z + 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z + 1));
	unsigned int a11 = calcAO(getBlock(c->x + x, c->y + y + 1, c->z + z + 1), getBlock(c->x + x + 1, c->y + y, c->z + z + 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z + 1));

	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		m_vertices.emplace_back(packData(x, y, z + 1, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z + 1, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z + 1, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z + 1, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
	} else {
		// Generate a flipped quad
		m_vertices.emplace_back(packData(x + 1, y, z + 1, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z + 1, a01, 1, _textureLayer));
		m_vertices.emplace_back(packData(x, y, z + 1, a00, 0, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y, z + 1, a10, 3, _textureLayer));
		m_vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		m_vertices.emplace_back(packData(x, y + 1, z + 1, a01, 1, _textureLayer));
	}
}

BlockTexture World::getTextureFromBlockID(uint8_t _blockID) {
	return m_blockTextures[_blockID - 1];
}

void tokenizeString(const std::string& _str, std::vector<std::string>& _tokens){
	_tokens.clear();
	_tokens.push_back(std::string());
	for(unsigned int i = 0; i < _str.size(); i++){
		if(_str[i] == ' '){
			_tokens.push_back(std::string());
		}else{
			_tokens.back().push_back(_str[i]);
		}
	}
}

void World::loadBlockTexturesFromFile(){
	std::ifstream is;
	is.open("TextureArrangement");
	if(is.fail()){
		std::cout << "Failed to open texture arrangment file, it should be under res/textures/texture_arrangement.txt" << std::endl;
		return;
	}

	std::string line;
	std::vector<std::string> tokens;
	while(std::getline(is, line)){
		tokenizeString(line, tokens);
		uint16_t top = std::stoi(tokens.at(0));
		uint16_t side = std::stoi(tokens.at(1));
		uint16_t bot = std::stoi(tokens.at(2));
		m_blockTextures.push_back(BlockTexture(top, side, bot));
	}

	is.close();
}
