#include "World.hpp"
#include <iostream>


void World::init(NetworkManager& _manager){
	m_data = static_cast<uint8_t*>(malloc(WORLD_WIDTH * WORLD_LENGTH * WORLD_HEIGHT * CHUNK_SIZE));
	_manager.downloadWorld(m_data);

	// Loading the texture atlass into a texture array
	m_texturePack.init("res/textures/sprite_sheet.png", 512);
	loadBlockTexturesFromFile();

	// Initializing the m_chunks
	m_chunks = new Chunk[WORLD_WIDTH * WORLD_LENGTH * WORLD_HEIGHT];
	for(unsigned int y = 0; y < WORLD_HEIGHT; y++){
		for(unsigned int z = 0; z < WORLD_LENGTH; z++){
			for(unsigned int x = 0; x < WORLD_WIDTH; x++){
				getChunk(x, y, z)->init(x * CHUNK_WIDTH, y * CHUNK_WIDTH, z * CHUNK_WIDTH);
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

	m_texturePack.bind();

	m_shader.loadProjectionMatrix(_camera.getProjectionMatrix());
	m_shader.loadViewMatrix(_camera.getViewMatrix());
	m_shader.loadCameraPosition(_camera.getPosition());

	for(unsigned int y = 0; y < WORLD_HEIGHT; y++){
		for(unsigned int z = 0; z < WORLD_LENGTH; z++){
			for(unsigned int x = 0; x < WORLD_WIDTH; x++){

				Chunk* c = getChunk(x, y, z);
				if(c->needsMeshUpdate){
					generateMesh(c);
					c->needsMeshUpdate = false;
				}

				if(c->getNumVertices()){
					unsigned int w = CHUNK_WIDTH;
					glm::vec3 min = glm::vec3(c->x, c->y, c->z);
					glm::vec3 max = min + glm::vec3(w, w, w);

					if(_camera.viewFrustum.IsBoxVisible(min, max)){
						m_shader.loadChunkPosition(c->x, c->y, c->z);
						c->render();
					}
				}

			}
		}
	}

	m_texturePack.unbind();

	m_shader.unbind();
}

void World::destroy(){
	for(unsigned int y = 0; y < WORLD_HEIGHT; y++){
		for(unsigned int z = 0; z < WORLD_LENGTH; z++){
			for(unsigned int x = 0; x < WORLD_WIDTH; x++){
				getChunk(x, y, z)->destroy();
			}
		}
	}
	m_texturePack.destroy();
	m_shader.destroy();
	delete[] m_chunks;
	free(m_data);
}

void World::generateMesh(Chunk* _chunk){
	sf::Clock c;
	m_vertices.resize(0);

	for(unsigned int y = 0; y < CHUNK_WIDTH; y++){
		for(unsigned int z = 0; z < CHUNK_WIDTH; z++){
			for(unsigned int x = 0; x < CHUNK_WIDTH; x++){
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
	unsigned int maxW = WORLD_WIDTH * CHUNK_WIDTH;
	unsigned int maxL = WORLD_LENGTH * CHUNK_WIDTH;
	unsigned int maxH = WORLD_HEIGHT * CHUNK_WIDTH;

	if(_x < 0 || _x >= maxW || _z < 0 || _z >= maxL || _y < 0 || _y >= maxH) return false;
	return true;
}

uint8_t World::getBlock(int _x, int _y, int _z){
	if(!isBlockInLocalWorld(_x, _y, _z)){
		return 0;
	}

	unsigned int maxW = WORLD_WIDTH * CHUNK_WIDTH;
	unsigned int maxL = WORLD_LENGTH * CHUNK_WIDTH;

	return m_data[(_y * maxW * maxL) + (_z * maxW) + _x];
}

void World::setBlock(int x, int y, int z, uint8_t block) {
	if(!isBlockInLocalWorld(x, y, z)){
		return;
	}

	unsigned int maxW = WORLD_WIDTH * CHUNK_WIDTH;
	unsigned int maxL = WORLD_LENGTH * CHUNK_WIDTH;

	// Getting the chunk the block is in
	unsigned int posX = x / CHUNK_WIDTH;
	unsigned int posY = y / CHUNK_WIDTH;
	unsigned int posZ = z / CHUNK_WIDTH;

	// Right now, we have the position of the chunk that the block has been placed in stored in posX, posY, and posZ
	// So we first of all, queue this chunk up for a mesh update
	getChunk(posX, posY, posZ)->needsMeshUpdate = true;

	// Setting the block based on chunk space coords
	m_data[(y * maxW * maxL) + (z * maxW) + x] = block;

	// Next, we check if the placed block has been placed on any edge
	// Update neighboring m_chunks if block is on the edge of the current chunk
	if(x % CHUNK_WIDTH == 0){
		Chunk* chunk = getChunk((posX - 1) % WORLD_WIDTH, posY, posZ);
		if(chunk) chunk->needsMeshUpdate = true;
	}
	if((x + 1) % CHUNK_WIDTH == 0){
		Chunk* chunk = getChunk((posX + 1) % WORLD_WIDTH, posY, posZ);
		if(chunk) chunk->needsMeshUpdate = true;
	}
	if(z % CHUNK_WIDTH == 0){
		Chunk* chunk = getChunk(posX, posY, (posZ - 1) % WORLD_LENGTH);
		if(chunk) chunk->needsMeshUpdate = true;
	}
	if((z + 1) % CHUNK_WIDTH == 0){
		Chunk* chunk = getChunk(posX, posY, (posZ + 1) % WORLD_LENGTH);
		if(chunk) chunk->needsMeshUpdate = true;
	}
	if(y % CHUNK_WIDTH == 0){
		Chunk* chunk = getChunk(posX, (posY - 1) % WORLD_HEIGHT, posZ);
		if(chunk) chunk->needsMeshUpdate = true;
	}
	if((y + 1) % CHUNK_WIDTH == 0){
		Chunk* chunk = getChunk(posX, (posY + 1) % WORLD_HEIGHT, posZ);
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
	if(_y < 0 || _y >= WORLD_HEIGHT || _x < 0 || _x >= WORLD_WIDTH || _z < 0 || _z >= WORLD_LENGTH){
		return nullptr;
	}
	return &m_chunks[(_y * WORLD_WIDTH * WORLD_LENGTH) + (_z * WORLD_WIDTH) + _x];
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
	is.open("res/textures/texture_arrangement.txt");
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

