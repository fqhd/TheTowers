#include "World.hpp"
#include "../../Constants.hpp"
#include <iostream>

void World::init(uint8_t* d){

	data = d;
	chunks = new Chunk[Constants::getLocalWorldWidth() * Constants::getLocalWorldWidth() * Constants::getWorldHeight()];

	for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
		for(unsigned int z = 0; z < Constants::getLocalWorldWidth(); z++){
			for(unsigned int x = 0; x < Constants::getLocalWorldWidth(); x++){

				getChunk(x, y, z)->init(x * Constants::getChunkWidth(), y * Constants::getChunkWidth(), z * Constants::getChunkWidth());

			}
		}
	}

	shader.init();

}

void World::render(Settings& settings, Camera& camera, const std::vector<vec3>& colors){

	Frustum f(camera.getProjectionMatrix() * camera.getViewMatrix());

	shader.bind();

	shader.loadProjectionMatrix(camera.getProjectionMatrix());
	shader.loadViewMatrix(camera.getViewMatrix());
	shader.loadGradient(settings.gradient);
	shader.loadDensity(settings.density);

	for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
		for(unsigned int z = 0; z < Constants::getLocalWorldWidth(); z++){
			for(unsigned int x = 0; x < Constants::getLocalWorldWidth(); x++){

				Chunk* c = getChunk(x, y, z);
				if(c->needsUpdate){
					generateMesh(colors, c);
					c->needsUpdate = false;
				}

				unsigned int w = Constants::getChunkWidth();
				glm::vec3 min = glm::vec3(c->x, c->y, c->z);
				glm::vec3 max = min + glm::vec3(w, w, w);

				if(f.IsBoxVisible(min, max)){
					shader.loadChunkPosition(c->x, c->y, c->z);
					c->render();
				}

			}
		}
	}

	shader.unbind();

}

void World::destroy(){

	for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
		for(unsigned int z = 0; z < Constants::getLocalWorldWidth(); z++){
			for(unsigned int x = 0; x < Constants::getLocalWorldWidth(); x++){

				getChunk(x, y, z)->destroy();

			}
		}
	}

	shader.destroy();
	delete[] chunks;

}

void World::generateMesh(const std::vector<vec3>& colors, Chunk* chunk){

	vertices.clear();

	for(unsigned int y = 0; y < Constants::getChunkWidth(); y++){

		for(unsigned int z = 0; z < Constants::getChunkWidth(); z++){

			for(unsigned int x = 0; x < Constants::getChunkWidth(); x++){

				//May be better to get the surrounding blocks and then check against them rather than get the surrounding blocks every time. Because then, they will be stored in the cache rather than having to go look through the entire array of data for the surrounding blocks in ram which is farther away from the cpu

				uint8_t block = getBlock(chunk->x + x, chunk->y + y, chunk->z + z);

				if(block){
					addBlock(chunk, x, y, z, colors[block]);
				}
			}
		}
	}

	chunk->pushData(vertices.data(), vertices.size());

}

uint8_t World::getBlock(int x, int y, int z){
	unsigned int maxW = Constants::getChunkWidth() * Constants::getWorldWidth();
	unsigned int maxH = Constants::getChunkWidth() * Constants::getWorldHeight();

	if(x < 0 || x >= maxW) return 0;
	if(y < 0 || y >= maxH) return 0;
	if(z < 0 || z >= maxW) return 0;
	
	return data[(y * maxW * maxW) + (z * maxW) + x];
}

void World::setBlock(int x, int y, int z, uint8_t block) {
	unsigned int maxW = Constants::getChunkWidth() * Constants::getWorldWidth();
	unsigned int maxH = Constants::getChunkWidth() * Constants::getWorldHeight();

	//Checking if the X Y Z coordinate of the block is in bounds
	if(y < 0 || y >= maxH) return;
	if(x < 0 || x >= maxW) return;
	if(z < 0 || z >= maxW) return;

	data[(y * maxW * maxW) + (z * maxW) + x] = block; //Updating the block in the array of block IDs

	// Getting the chunk that the block is in
	unsigned int posX = x / Constants::getChunkWidth();
	unsigned int posY = y / Constants::getChunkWidth();
	unsigned int posZ = z / Constants::getChunkWidth();

	//Right now, we have the position of the chunk that the block has been placed in stored in posX, posY, and posZ
	//So we first of all, queue this chunk up for updation
	getChunk(posX, posY, posZ)->needsUpdate = true;

	//Next, we check if the placed block has been placed on any edge
	//Update neighboring chunks if block is on the edge of the current chunk
	if(x % Constants::getChunkWidth() == 0){
		Chunk* chunk = getChunk(posX - 1, posY, posZ);
		if(chunk) chunk->needsUpdate = true;
	}
	if((x + 1) % Constants::getChunkWidth() == 0){
		Chunk* chunk = getChunk(posX + 1, posY, posZ);
		if(chunk) chunk->needsUpdate = true;
	}
	if(z % Constants::getChunkWidth() == 0){
		Chunk* chunk = getChunk(posX, posY, posZ - 1);
		if(chunk) chunk->needsUpdate = true;
	}
	if((z + 1) % Constants::getChunkWidth() == 0){
		Chunk* chunk = getChunk(posX, posY, posZ + 1);
		if(chunk) chunk->needsUpdate = true;
	}
	if(y % Constants::getChunkWidth() == 0){
		Chunk* chunk = getChunk(posX, posY - 1, posZ);
		if(chunk) chunk->needsUpdate = true;
	}
	if((y + 1) % Constants::getChunkWidth() == 0){
		Chunk* chunk = getChunk(posX, posY + 1, posZ);
		if(chunk) chunk->needsUpdate = true;
	}

}

void World::addBlock(Chunk* _c, int _x, int _y, int _z, const vec3& _color){

	addTopFace(_c, _x, _y, _z, _color);
	addBottomFace(_c, _x, _y, _z, _color);
	addLeftFace(_c, _x, _y, _z, _color);
	addRightFace(_c, _x, _y, _z, _color);
	addFrontFace(_c, _x, _y, _z, _color);
	addBackFace(_c, _x, _y, _z, _color);

}

Chunk* World::getChunk(int x, int y, int z) {
	unsigned int worldWidth = Constants::getLocalWorldWidth();
	unsigned int worldHeight = Constants::getWorldHeight();

	if(y < 0 || y >= worldHeight) return nullptr;
	if(x < 0 || x >= worldWidth) return nullptr;
	if(z < 0 || z >= worldWidth) return nullptr;
	
	return &chunks[(y * worldWidth * worldWidth) + (z * worldWidth) + x];
}

unsigned int calcAO(bool side1, bool side2, bool corner){
	if(side1 && side2){
		return 0;
	}
	return 3 - (side1 + side2 + corner);
}

void World::addTopFace(Chunk* c, int x, int y, int z, const vec3& color){
	if(getBlock(c->x + x, c->y + y + 1, c->z + z)) return;

	float of = 1.0f;
	unsigned int a00 = calcAO(getBlock(c->x + x, c->y + y + 1, c->z + z - 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z), getBlock(c->x + x - 1, c->y + y + 1, c->z + z - 1));
	unsigned int a01 = calcAO(getBlock(c->x + x - 1, c->y + y + 1, c->z + z), getBlock(c->x + x, c->y + y + 1, c->z + z + 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z + 1));
	unsigned int a11 = calcAO(getBlock(c->x + x, c->y + y + 1, c->z + z + 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z), getBlock(c->x + x + 1, c->y + y + 1, c->z + z + 1));
	unsigned int a10 = calcAO(getBlock(c->x + x, c->y + y + 1, c->z + z - 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z), getBlock(c->x + x + 1, c->y + y + 1, c->z + z - 1));

	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
	} else {
		// Generate flipped quad
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
	}



}

void World::addBottomFace(Chunk* c, int x, int y, int z, const vec3& color){
	if(getBlock(c->x + x, c->y + y - 1, c->z + z)) return;

	float of = 1.0f;

	unsigned int a00 = calcAO(getBlock(c->x + x, c->y + y - 1, c->z + z - 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z), getBlock(c->x + x - 1, c->y + y - 1, c->z + z - 1));
	unsigned int a01 = calcAO(getBlock(c->x + x - 1, c->y + y - 1, c->z + z), getBlock(c->x + x, c->y + y - 1, c->z + z + 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z + 1));
	unsigned int a10 = calcAO(getBlock(c->x + x, c->y + y - 1, c->z + z - 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z), getBlock(c->x + x + 1, c->y + y - 1, c->z + z - 1));
	unsigned int a11 = calcAO(getBlock(c->x + x, c->y + y - 1, c->z + z + 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z), getBlock(c->x + x + 1, c->y + y - 1, c->z + z + 1));
	
	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	} else {
		// Generate flipped quad
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
	}

}

void World::addRightFace(Chunk* c, int x, int y, int z, const vec3& color){
	if(getBlock(c->x + x - 1, c->y + y, c->z + z)) return;

	float of = 1.0f;

	unsigned int a00 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z - 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z), getBlock(c->x + x - 1, c->y + y - 1, c->z + z - 1));
	unsigned int a01 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z - 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z), getBlock(c->x + x - 1, c->y + y + 1, c->z + z - 1));
	unsigned int a10 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z + 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z), getBlock(c->x + x - 1, c->y + y - 1, c->z + z + 1));
	unsigned int a11 = calcAO(getBlock(c->x + x - 1, c->y + y + 1, c->z + z), getBlock(c->x + x - 1, c->y + y, c->z + z + 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z + 1));


	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
	} else {
		// Generate flipped quad
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
	}
}

void World::addLeftFace(Chunk* c, int x, int  y, int z, const vec3& color){
	if(getBlock(c->x + x + 1, c->y + y, c->z + z)) return;

	float of = 1.0f;

	unsigned int a00 = calcAO(getBlock(c->x + x + 1, c->y + y, c->z + z - 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z), getBlock(c->x + x + 1, c->y + y - 1, c->z + z - 1));
	unsigned int a01 = calcAO(getBlock(c->x + x + 1, c->y + y, c->z + z - 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z), getBlock(c->x + x + 1, c->y + y + 1, c->z + z - 1));
	unsigned int a10 = calcAO(getBlock(c->x + x + 1, c->y + y, c->z + z + 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z), getBlock(c->x + x + 1, c->y + y - 1, c->z + z + 1));
	unsigned int a11 = calcAO(getBlock(c->x + x + 1, c->y + y + 1, c->z + z), getBlock(c->x + x + 1, c->y + y, c->z + z + 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z + 1));

	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
	} else {
		// Generate flipped quad
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));
	}
	

}

void World::addFrontFace(Chunk* c, int x, int y, int z, const vec3& color){
	if(getBlock(c->x + x, c->y + y, c->z + z - 1)) return;

	float of = 1.0f;

	unsigned int a00 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z - 1), getBlock(c->x + x, c->y + y - 1, c->z + z - 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z - 1));
	unsigned int a01 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z - 1), getBlock(c->x + x, c->y + y + 1, c->z + z - 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z - 1));
	unsigned int a10 = calcAO(getBlock(c->x + x, c->y + y - 1, c->z + z - 1), getBlock(c->x + x + 1, c->y + y, c->z + z - 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z - 1));
	unsigned int a11 = calcAO(getBlock(c->x + x, c->y + y + 1, c->z + z - 1), getBlock(c->x + x + 1, c->y + y, c->z + z - 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z - 1));

	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));
	} else {
		// Generate flipped quad
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));
	}


}

void World::addBackFace(Chunk* c, int x, int y, int z, const vec3& color){
	if(getBlock(c->x + x, c->y + y, c->z + z + 1)) return;

	float of = 1.0f;

	unsigned int a00 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z + 1), getBlock(c->x + x, c->y + y - 1, c->z + z + 1), getBlock(c->x + x - 1, c->y + y - 1, c->z + z + 1));
	unsigned int a01 = calcAO(getBlock(c->x + x - 1, c->y + y, c->z + z + 1), getBlock(c->x + x, c->y + y + 1, c->z + z + 1), getBlock(c->x + x - 1, c->y + y + 1, c->z + z + 1));
	unsigned int a10 = calcAO(getBlock(c->x + x, c->y + y - 1, c->z + z + 1), getBlock(c->x + x + 1, c->y + y, c->z + z + 1), getBlock(c->x + x + 1, c->y + y - 1, c->z + z + 1));
	unsigned int a11 = calcAO(getBlock(c->x + x, c->y + y + 1, c->z + z + 1), getBlock(c->x + x + 1, c->y + y, c->z + z + 1), getBlock(c->x + x + 1, c->y + y + 1, c->z + z + 1));

	if(a00 + a11 > a01 + a10) {
		// Generate normal quad
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
	} else {
		// Generate a flipped quad
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a00 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a10 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a11 / 3.0f;
		vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
		of = a01 / 3.0f;
		vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));
	}


}
