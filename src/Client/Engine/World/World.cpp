#include "World.hpp"
#include <iostream>


const unsigned int WORLD_WIDTH = 4;
const unsigned int WORLD_HEIGHT = 2;

void World::init(NetworkManager& _manager){

	// Downloading the world
	data = static_cast<uint8_t*>(malloc(WORLD_WIDTH * WORLD_WIDTH * WORLD_HEIGHT * CHUNK_SIZE));
	// data = new uint8_t[WORLD_WIDTH * WORLD_WIDTH * WORLD_HEIGHT * CHUNK_SIZE];
	// _manager.downloadWorld(data, WORLD_WIDTH * WORLD_WIDTH * WORLD_HEIGHT * CHUNK_SIZE);

	// Loading the texture atlass into a texture array
	texturePack.init("res/textures/sprite_sheet.png", 512);

	// Initializing the chunks
	chunks = new Chunk[WORLD_WIDTH * WORLD_WIDTH * WORLD_HEIGHT];
	unsigned int index = 0;
	for(unsigned int y = 0; y < WORLD_HEIGHT; y++){
		for(unsigned int z = 0; z < WORLD_WIDTH; z++){
			for(unsigned int x = 0; x < WORLD_WIDTH; x++){
				getChunk(x, y, z)->init(x * CHUNK_WIDTH, y * CHUNK_WIDTH, z * CHUNK_WIDTH, data + index * CHUNK_SIZE);
				index++;
			}
		}
	}

	// Initializing the shader
	shader.init();

	setBlock(0, 0, 0, 1);
	setBlock(1, 1, 1, 1);
	setBlock(0, 0, 3, 1);
	setBlock(0, 43, 0, 4);

}

GLuint World::packData(uint8_t x, uint8_t y, uint8_t z, uint8_t lightLevel, uint8_t textureCoordinateIndex, uint16_t textureArrayIndex) {
	GLuint vertex = x | y << 6 | z << 12 | lightLevel << 18 | textureCoordinateIndex << 21 | textureArrayIndex << 23;
	return vertex;
}

void World::update(InputManager* _manager){
	if(_manager->isKeyPressed(GLFW_KEY_L)){
		moveLeft();
	}
	if(_manager->isKeyPressed(GLFW_KEY_R)){
		moveRight();
	}
	if(_manager->isKeyPressed(GLFW_KEY_F)){
		moveFront();
	}
	if(_manager->isKeyPressed(GLFW_KEY_B)){
		moveBack();
	}
}

void World::render(Camera& _camera){

	std::cout << (unsigned int)getBlock(0, 43, 0) << std::endl;

	shader.bind();

	texturePack.bind();

	shader.loadProjectionMatrix(_camera.getProjectionMatrix());
	shader.loadViewMatrix(_camera.getViewMatrix());
	shader.loadCameraPosition(_camera.getPosition());

	for(unsigned int y = 0; y < WORLD_HEIGHT; y++){
		for(unsigned int z = 0; z < WORLD_WIDTH; z++){
			for(unsigned int x = 0; x < WORLD_WIDTH; x++){

				Chunk* c = getChunk(x, y, z);
				if(c->needsUpdate){
					generateMesh(c);
					c->needsUpdate = false;
				}

				if(c->getNumVertices()){
					unsigned int w = CHUNK_WIDTH;
					glm::vec3 min = glm::vec3(c->x, c->y, c->z);
					glm::vec3 max = min + glm::vec3(w, w, w);

					if(_camera.viewFrustum.IsBoxVisible(min, max)){
						shader.loadChunkPosition(c->x, c->y, c->z);
						c->render();
					}
				}

			}
		}
	}

	texturePack.unbind();

	shader.unbind();

}

void World::destroy(){
	for(unsigned int y = 0; y < WORLD_HEIGHT; y++){
		for(unsigned int z = 0; z < WORLD_WIDTH; z++){
			for(unsigned int x = 0; x < WORLD_WIDTH; x++){
				getChunk(x, y, z)->destroy();
			}
		}
	}
	texturePack.destroy();
	shader.destroy();
	delete[] chunks;
	free(data);
}

void World::generateMesh(Chunk* chunk){
	vertices.clear();
	for(unsigned int y = 0; y < CHUNK_WIDTH; y++){
		for(unsigned int z = 0; z < CHUNK_WIDTH; z++){
			for(unsigned int x = 0; x < CHUNK_WIDTH; x++){
				//May be better to get the surrounding blocks and then check against them rather than get the surrounding blocks every time. Because then, they will be stored in the cache rather than having to go look through the entire array of data for the surrounding blocks in ram which is farther away from the cpu
				uint8_t block = getBlock(chunk->x + x, chunk->y + y, chunk->z + z);

				if(block){
					addBlock(chunk, x, y, z, block);
				}
			}
		}
	}

	chunk->pushData(vertices.data(), vertices.size());

}

uint8_t World::getBlock(int x, int y, int z){
	unsigned int maxW = CHUNK_WIDTH * WORLD_WIDTH;
	unsigned int maxH = CHUNK_WIDTH * WORLD_HEIGHT;

	// Converting coords from global space to local space
	x = x % maxW;
	z = z % maxW;
	if(y < 0 || y >= maxH) return 0;

	uint8_t block = getChunk(x / CHUNK_WIDTH, y / CHUNK_WIDTH, z / CHUNK_WIDTH)->getBlock(x % CHUNK_WIDTH, y % CHUNK_WIDTH, z % CHUNK_WIDTH);
	if(block){
		std::cout << "block" << std::endl;
	}
	return block;
}

void World::setBlock(int x, int y, int z, uint8_t block) {
	unsigned int maxW = CHUNK_WIDTH * WORLD_WIDTH;
	unsigned int maxH = CHUNK_WIDTH * WORLD_HEIGHT;

	// Converting coords from global space to local space
	if(y < 0 || y >= maxH) return;
	x = x % maxW;
	z = z % maxW;

	// Getting the chunk that the block is in
	unsigned int posX = x / CHUNK_WIDTH;
	unsigned int posY = y / CHUNK_WIDTH;
	unsigned int posZ = z / CHUNK_WIDTH;

	// Right now, we have the position of the chunk that the block has been placed in stored in posX, posY, and posZ
	// So we first of all, queue this chunk up for a mesh update
	getChunk(posX, posY, posZ)->needsUpdate = true;

	// Setting the block based on chunk space coords
	getChunk(posX, posY, posZ)->setBlock(x % CHUNK_WIDTH, y % CHUNK_WIDTH, z % CHUNK_WIDTH, block);
	

	//Next, we check if the placed block has been placed on any edge
	//Update neighboring chunks if block is on the edge of the current chunk
	// if(x % CHUNK_WIDTH == 0){
	// 	Chunk* chunk = getChunk(posX - 1, posY, posZ);
	// 	if(chunk) chunk->needsUpdate = true;
	// }
	// if((x + 1) % CHUNK_WIDTH == 0){
	// 	Chunk* chunk = getChunk(posX + 1, posY, posZ);
	// 	if(chunk) chunk->needsUpdate = true;
	// }
	// if(z % CHUNK_WIDTH == 0){
	// 	Chunk* chunk = getChunk(posX, posY, posZ - 1);
	// 	if(chunk) chunk->needsUpdate = true;
	// }
	// if((z + 1) % CHUNK_WIDTH == 0){
	// 	Chunk* chunk = getChunk(posX, posY, posZ + 1);
	// 	if(chunk) chunk->needsUpdate = true;
	// }
	// if(y % CHUNK_WIDTH == 0){
	// 	Chunk* chunk = getChunk(posX, posY - 1, posZ);
	// 	if(chunk) chunk->needsUpdate = true;
	// }
	// if((y + 1) % CHUNK_WIDTH == 0){
	// 	Chunk* chunk = getChunk(posX, posY + 1, posZ);
	// 	if(chunk) chunk->needsUpdate = true;
	// }

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

Chunk* World::getChunk(int x, int y, int z) {
	if(y < 0 || y >= WORLD_HEIGHT){
		std::cout << "get chunk segfault" << std::endl;
		return nullptr;
	}
	if(x < 0 || x >= WORLD_WIDTH){
		std::cout << "get chunk segfault" << std::endl;
		return nullptr;
	}
	if(z < 0 || z >= WORLD_WIDTH){
		std::cout << "get chunk segfault" << std::endl;
		return nullptr;
	}
	
	return &chunks[(y * WORLD_WIDTH * WORLD_WIDTH) + (z * WORLD_WIDTH) + x];
}

void World::moveLeft(){
	for(unsigned int j = 0; j < WORLD_HEIGHT; j++){
		for(unsigned int i = 0; i < WORLD_WIDTH; i++){
			Chunk* c = getChunk(m_chunkOffsetX % WORLD_WIDTH, j, i);
			c->x += WORLD_WIDTH * CHUNK_WIDTH;
			c->needsUpdate = true;
		}
	}
	m_chunkOffsetX++;
}

void World::moveRight(){
	for(unsigned int j = 0; j < WORLD_HEIGHT; j++){
		for(unsigned int i = 0; i < WORLD_WIDTH; i++){
			Chunk* c = getChunk(((WORLD_WIDTH - 1) + m_chunkOffsetX) % WORLD_WIDTH, j, i);
			c->x -= WORLD_WIDTH * CHUNK_WIDTH;
			c->needsUpdate = true;
		}
	}
	m_chunkOffsetX--;
}

void World::moveFront(){
	for(unsigned int j = 0; j < WORLD_HEIGHT; j++){
		for(unsigned int i = 0; i < WORLD_WIDTH; i++){
			Chunk* c = getChunk(i, j, m_chunkOffsetZ % WORLD_WIDTH);
			c->z += WORLD_WIDTH * CHUNK_WIDTH;
			c->needsUpdate = true;
		}
	}
	m_chunkOffsetZ++;
}

void World::moveBack(){
	for(unsigned int j = 0; j < WORLD_HEIGHT; j++){
		for(unsigned int i = 0; i < WORLD_WIDTH; i++){
			Chunk* c = getChunk(i, j, ((WORLD_WIDTH - 1) + m_chunkOffsetZ) % WORLD_WIDTH);
			c->z -= WORLD_WIDTH * CHUNK_WIDTH;
			c->needsUpdate = true;
		}
	}
	m_chunkOffsetZ--;
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
		vertices.emplace_back(packData(x, y + 1, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z + 1, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z, a10, 3, _textureLayer));
	} else {
		// Generate flipped quad
		vertices.emplace_back(packData(x + 1, y + 1, z, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z + 1, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z + 1, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
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
		vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z + 1, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x, y, z + 1, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z + 1, a11, 2, _textureLayer));

	} else {
		// Generate flipped quad
		vertices.emplace_back(packData(x + 1, y, z, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x, y, z + 1, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z + 1, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x, y, z + 1, a01, 1, _textureLayer));
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
		vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z + 1, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x, y, z + 1, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z + 1, a11, 2, _textureLayer));
	} else {
		// Generate flipped quad
		vertices.emplace_back(packData(x, y, z + 1, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x, y, z + 1, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z + 1, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z, a01, 1, _textureLayer));
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
		vertices.emplace_back(packData(x + 1, y, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z + 1, a10, 3, _textureLayer));
	} else {
		// Generate flipped quad
		vertices.emplace_back(packData(x + 1, y + 1, z, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z + 1, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z + 1, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z, a00, 0, _textureLayer));
	}

}

BlockTexture World::getTextureFromBlockID(uint8_t _blockID) {
	// Space reserved for uni-textured blocks(blocks that have the same texture on all sides)
	uint16_t offset = 255;
	
	// List of exceptions
	if (_blockID == 1) { // Grass
		return BlockTexture(0, offset, 3);
	} else if (_blockID == 3) { // Snow
		return BlockTexture(2, offset + 1, 3);
	} else if (_blockID == 6) { // Wood Log
		return BlockTexture(5, offset + 2, 5);
	}

	return BlockTexture(_blockID - 1);
}


void World::addFrontFace(Chunk* c, uint8_t x, uint8_t y, uint8_t z, uint16_t _textureLayer){
	if(getBlock(c->x + x, c->y + y, c->z + z - 1)) return;

	unsigned int a00 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z - 1), getBlock(c->x + x, c->y + y - 1, c->z + z - 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z - 1));
	unsigned int a01 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z - 1), getBlock(c->x + x, c->y + y + 1, c->z + z - 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z - 1));
	unsigned int a10 = calcAO(getBlock(c->x + x, c->y + y - 1, c->z + z - 1), getBlock(c->x + x + 1, c->y + y, c->z + z - 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z - 1));
	unsigned int a11 = calcAO(getBlock(c->x + x, c->y + y + 1, c->z + z - 1), getBlock(c->x + x + 1, c->y + y, c->z + z - 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z - 1));

	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z, a10, 3, _textureLayer));
	} else {
		// Generate flipped quad
		vertices.emplace_back(packData(x + 1, y, z, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x, y, z, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z, a11, 2, _textureLayer));
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
		vertices.emplace_back(packData(x, y, z + 1, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z + 1, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x, y, z + 1, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z + 1, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
	} else {
		// Generate a flipped quad
		vertices.emplace_back(packData(x + 1, y, z + 1, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z + 1, a01, 1, _textureLayer));
		vertices.emplace_back(packData(x, y, z + 1, a00, 0, _textureLayer));
		vertices.emplace_back(packData(x + 1, y, z + 1, a10, 3, _textureLayer));
		vertices.emplace_back(packData(x + 1, y + 1, z + 1, a11, 2, _textureLayer));
		vertices.emplace_back(packData(x, y + 1, z + 1, a01, 1, _textureLayer));
	}

}
