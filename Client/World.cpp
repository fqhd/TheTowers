#include "World.hpp"
#include "Constants.hpp"

void World::init(uint8_t* d){

     m_data = d;
     m_chunks = new Chunk[Constants::getLocalWorldWidth() * Constants::getLocalWorldWidth() * Constants::getWorldHeight()];

     for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
          for(unsigned int z = 0; z < Constants::getLocalWorldWidth(); z++){
               for(unsigned int x = 0; x < Constants::getLocalWorldWidth(); x++){

                    getChunk(x, y, z)->init(x * Constants::getChunkWidth(), y * Constants::getChunkWidth(), z * Constants::getChunkWidth());

               }
          }
     }

     m_shader.init();

}

void World::update(const std::vector<vec3>& colors, const glm::vec3& previousCameraPosition, const glm::vec3& currentCameraPosition){

     glm::uvec3 pGridPosition = glm::vec3(previousCameraPosition.x / Constants::getChunkWidth(), previousCameraPosition.y / Constants::getChunkWidth(), previousCameraPosition.z / Constants::getChunkWidth());
     glm::uvec3 cGridPosition = glm::vec3(currentCameraPosition.x / Constants::getChunkWidth(), currentCameraPosition.y / Constants::getChunkWidth(), currentCameraPosition.z / Constants::getChunkWidth());

     glm::uvec3 dPosition = pGridPosition - cGridPosition;

     if(dPosition.x == 1){
          moveLeft();
     }
     if(dPosition.x == -1){
          moveRight();
     }
     if(dPosition.z == 1){
          moveBack();
     }
     if(dPosition.z == -1){
          moveFront();
     }

}



void World::render(Settings& settings, Camera& camera, const std::vector<vec3>& colors){

     updateChunks(colors);

     Frustum f(camera.getProjectionMatrix() * camera.getViewMatrix());

     m_shader.bind();

     m_shader.loadProjectionMatrix(camera.getProjectionMatrix());
     m_shader.loadViewMatrix(camera.getViewMatrix());
     m_shader.loadGradient(settings.gradient);
     m_shader.loadDensity(settings.density);

	for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
		for(unsigned int z = 0; z < Constants::getLocalWorldWidth(); z++){
			for(unsigned int x = 0; x < Constants::getLocalWorldWidth(); x++){

				Chunk* c = getChunk(x, y, z);
				if(c->needsPush){
					c->pushData();
					c->needsPush = false;
				}

                    unsigned int w = Constants::getChunkWidth();
                    glm::vec3 min = glm::vec3(c->getX(), c->getY(), c->getZ());
                    glm::vec3 max = min + glm::vec3(w, w, w);

                    if(f.IsBoxVisible(min, max)){
                         c->render();
                    }

               }
          }
     }

     m_shader.unbind();

}

void World::updateChunks(const std::vector<vec3>& colors){
	for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
		for(unsigned int z = 0; z < Constants::getLocalWorldWidth(); z++){
			for(unsigned int x = 0; x < Constants::getLocalWorldWidth(); x++){
				Chunk* c = getChunk(x, y, z);
				if(c->needsUpdate){
					generateMesh(colors, c);
					c->needsUpdate = false;
					c->needsPush = true;
				}
			}
		}
	}
}

void World::moveFront(){

     for(unsigned int i = 0; i < Constants::getLocalWorldWidth(); i++){
          for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
               Chunk* currentChunk = getChunk(i, y, 0);
               currentChunk->setZ(currentChunk->getZ() + Constants::getLocalWorldWidth() * Constants::getChunkWidth());
               currentChunk->needsUpdate = true;
          }
     }
     m_chunkOffsetZ++;

}

void World::moveBack(){

     for(unsigned int i = 0; i < Constants::getLocalWorldWidth(); i++){
          for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
               Chunk* currentChunk = getChunk(i, y, Constants::getLocalWorldWidth() - 1);
               currentChunk->setZ(currentChunk->getZ() - Constants::getLocalWorldWidth() * Constants::getChunkWidth());
               currentChunk->needsUpdate = true;
          }
     }

     m_chunkOffsetZ--;

}

void World::moveRight(){

     for(unsigned int i = 0; i < Constants::getLocalWorldWidth(); i++){
          for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
               Chunk* currentChunk = getChunk(0, y, i);
               currentChunk->setX(currentChunk->getX() + Constants::getLocalWorldWidth() * Constants::getChunkWidth());
               currentChunk->needsUpdate = true;
          }
     }

     m_chunkOffsetX++;

}

void World::moveLeft(){

     for(unsigned int i = 0; i < Constants::getLocalWorldWidth(); i++){
          for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
               Chunk* currentChunk = getChunk(Constants::getLocalWorldWidth() - 1, y, i);
               currentChunk->setX(currentChunk->getX() - Constants::getLocalWorldWidth() * Constants::getChunkWidth());
               currentChunk->needsUpdate = true;
          }
     }

     m_chunkOffsetX--;

}



void World::destroy(){

	for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
		for(unsigned int z = 0; z < Constants::getLocalWorldWidth(); z++){
			for(unsigned int x = 0; x < Constants::getLocalWorldWidth(); x++){

				getChunk(x, y, z)->destroy();

			}
		}
	}

	m_shader.destroy();
	delete[] m_chunks;

}

void World::generateMesh(const std::vector<vec3>& colors, Chunk* chunk){

	chunk->vertices.clear();

     for(unsigned int y = 0; y < Constants::getChunkWidth(); y++){

          for(unsigned int z = 0; z < Constants::getChunkWidth(); z++){

               for(unsigned int x = 0; x < Constants::getChunkWidth(); x++){

				//May be better to get the surrounding blocks and then check against them rather than get the surrounding blocks every time. Because then, they will be stored in the cache rather than having to go look through the entire array of data for the surrounding blocks in ram which is farther away from the cpu


				uint8_t block = getBlock(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z);

                    if(block){
                         addTopFace(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z, colors[block], chunk->vertices);
                         addBottomFace(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z, colors[block], chunk->vertices);
                         addLeftFace(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z, colors[block], chunk->vertices);
                         addRightFace(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z, colors[block], chunk->vertices);
                         addFrontFace(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z, colors[block], chunk->vertices);
                         addBackFace(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z, colors[block], chunk->vertices);
                    }
               }
          }
     }

}

uint8_t World::getBlock(int x, int y, int z){

	unsigned int maxW = Constants::getChunkWidth() * Constants::getWorldWidth();
	unsigned int maxH = Constants::getChunkWidth() * Constants::getWorldHeight();

	if(y < 0 || y >= maxH) return 0;

	x = x % maxW;
	z = z % maxW;

	return m_data[(y * maxW * maxW) + (z * maxW) + x];

}

void World::setBlock(int x, int y, int z, uint8_t block) {
     unsigned int maxW = Constants::getChunkWidth() * Constants::getWorldWidth();
     unsigned int maxH = Constants::getChunkWidth() * Constants::getWorldHeight();

	unsigned int maxCW = Constants::getChunkWidth() * Constants::getLocalWorldWidth();
	unsigned int maxCH = Constants::getChunkWidth() * Constants::getLocalWorldWidth();

	//Checking if the Y is in bounds
	if(y < 0 || y >= maxH) return;

	x = x % maxW;
	z = z % maxW;

     m_data[(y * maxW * maxW) + (z * maxW) + x] = block; //Updating the block in the array of block IDs

     unsigned int posX = (x % maxCW) / Constants::getChunkWidth();
     unsigned int posY = y / Constants::getChunkWidth();
     unsigned int posZ = (z % maxCW) / Constants::getChunkWidth();

     posX -= m_chunkOffsetX;
     posZ -= m_chunkOffsetZ;

     getChunk(posX, posY, posZ)->needsUpdate = true;

     //Update neighboring chunks if block is on the edge of the current chunk
	if(x % Constants::getChunkWidth() == 0){
		Chunk* chunk = getChunk(posX - 1, posY, posZ);
		chunk->needsUpdate = true;
	}
	if((x + 1) % Constants::getChunkWidth() == 0){
		Chunk* chunk = getChunk(posX + 1, posY, posZ);
		chunk->needsUpdate = true;
	}
     if(z % Constants::getChunkWidth() == 0){
		Chunk* chunk = getChunk(posX, posY, posZ - 1);
		chunk->needsUpdate = true;
	}
	if((z + 1) % Constants::getChunkWidth() == 0){
		Chunk* chunk = getChunk(posX, posY, posZ + 1);
		chunk->needsUpdate = true;
	}
     if(y % Constants::getChunkWidth() == 0){
		Chunk* chunk = getChunk(posX, posY - 1, posZ);
		chunk->needsUpdate = true;
	}
	if((y + 1) % Constants::getChunkWidth() == 0){
		Chunk* chunk = getChunk(posX, posY + 1, posZ);
		chunk->needsUpdate = true;
	}
}


Chunk* World::getChunk(int x, int y, int z) {

     unsigned int worldWidth = Constants::getLocalWorldWidth();
     unsigned int worldHeight = Constants::getWorldHeight();

     if(y < 0 || y >= worldHeight) return nullptr;

     z = (z + m_chunkOffsetZ) % worldWidth;
     x = (x + m_chunkOffsetX) % worldWidth;
     return &m_chunks[(y * worldWidth * worldWidth) + (z * worldWidth) + x];

}

void World::addTopFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){

	if(getBlock(x, y + 1, z)) return;

	float of = 1.0f;

	of = (getBlock(x, y + 1, z - 1) || getBlock(x - 1, y + 1, z - 1) || getBlock(x - 1, y + 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y + 1, z) || getBlock(x - 1, y + 1, z + 1) || getBlock(x, y + 1, z + 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z + 1) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y + 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z - 1) || getBlock(x - 1, y + 1, z - 1) || getBlock(x - 1, y + 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z + 1) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y + 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z - 1) || getBlock(x + 1, y + 1, z - 1) || getBlock(x + 1, y + 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

}

void World::addBottomFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x, y - 1, z)) return;

	float of = 1.0f;

	of = (getBlock(x, y - 1, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x - 1, y - 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z + 1) || getBlock(x + 1, y - 1, z + 1) || getBlock(x + 1, y- 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y- 1, z) || getBlock(x - 1, y- 1, z + 1) || getBlock(x, y- 1, z + 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x - 1, y - 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z - 1) || getBlock(x + 1, y - 1, z - 1) || getBlock(x + 1, y - 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z + 1) || getBlock(x + 1, y - 1, z + 1) || getBlock(x + 1, y - 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

}

void World::addRightFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x - 1, y, z)) return;

	float of = 1.0f;

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x - 1, y - 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y + 1, z) || getBlock(x - 1, y + 1, z + 1) || getBlock(x - 1, y, z + 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y + 1, z - 1) || getBlock(x - 1, y + 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x - 1, y - 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z + 1) || getBlock(x - 1, y - 1, z + 1) || getBlock(x - 1, y - 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y + 1, z) || getBlock(x - 1, y + 1, z + 1) || getBlock(x - 1, y, z + 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

}

void World::addLeftFace(int x, int  y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x + 1, y, z)) return;

	float of = 1.0f;

	of = (getBlock(x + 1, y, z - 1) || getBlock(x + 1, y - 1, z - 1) || getBlock(x + 1, y - 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y, z - 1) || getBlock(x + 1, y + 1, z - 1) || getBlock(x + 1, y + 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y + 1, z) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y, z + 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y, z - 1) || getBlock(x + 1, y - 1, z - 1) || getBlock(x + 1, y - 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y + 1, z) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y, z + 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y, z + 1) || getBlock(x + 1, y - 1, z + 1) || getBlock(x + 1, y - 1, z)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

}

void World::addFrontFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x, y, z - 1)) return;

	float of = 1.0f;

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x, y - 1, z - 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y + 1, z - 1) || getBlock(x, y + 1, z - 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z - 1) || getBlock(x + 1, y + 1, z - 1) || getBlock(x + 1, y, z - 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x, y - 1, z - 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z - 1) || getBlock(x + 1, y + 1, z - 1) || getBlock(x + 1, y, z - 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z - 1) || getBlock(x + 1, y - 1, z - 1) || getBlock(x + 1, y, z - 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));
}

void World::addBackFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x, y, z + 1)) return;

	float of = 1.0f;

	of = (getBlock(x - 1, y, z + 1) || getBlock(x - 1, y - 1, z + 1) || getBlock(x, y - 1, z + 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z + 1) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y, z + 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z + 1) || getBlock(x - 1, y + 1, z + 1) || getBlock(x, y + 1, z + 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z + 1) || getBlock(x - 1, y - 1, z + 1) || getBlock(x, y - 1, z + 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z + 1) || getBlock(x + 1, y - 1, z + 1) || getBlock(x + 1, y, z + 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z + 1) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y, z + 1)) ? Constants::getOcclusionFactor() : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

}
