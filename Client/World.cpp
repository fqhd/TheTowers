#include "World.hpp"
#include "Constants.hpp"


void World::init(uint8_t* d){

     data = d;
     m_chunks = new Chunk[Constants::getWorldWidth() * Constants::getWorldWidth() * Constants::getWorldHeight()];

     for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
          for(unsigned int z = 0; z < Constants::getWorldWidth(); z++){
               for(unsigned int x = 0; x < Constants::getWorldWidth(); x++){

                    getChunk(x, y, z)->init(x * Constants::getChunkWidth(), y * Constants::getChunkWidth(), z * Constants::getChunkWidth());

                    Utils::log("hi");

               }
          }
     }

     m_chunkShader.loadShader("res/shaders/chunkVertex.glsl", "res/shaders/chunkFragment.glsl");
     m_chunkShader.getUniformLocations();
}

void World::render(Camera& camera, const std::vector<vec3>& colors, float range){

     m_chunkShader.bind();
     m_chunkShader.loadMatrix(camera.getProjectionMatrix() * camera.getViewMatrix());

     for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
          for(unsigned int z = 0; z < Constants::getWorldWidth(); z++){
               for(unsigned int x = 0; x < Constants::getWorldWidth(); x++){

                    if(getChunk(x, y, z)->needsUpdate){
                         generateMesh(colors, getChunk(x, y, z));
                         getChunk(x, y, z)->needsUpdate = false;
                    }


                    if(Utils::isInRange(camera.getPosition(), glm::vec3(getChunk(x, y, z)->getX() + Constants::getChunkWidth() / 2,
                    getChunk(x, y, z)->getY() + Constants::getChunkWidth() / 2, getChunk(x, y, z)->getZ() + Constants::getChunkWidth() / 2), range) && getChunk(x, y, z)->getNumVertices()) {
                         getChunk(x, y, z)->render();
                    }

               }
          }
     }



     m_chunkShader.unbind();

}

void World::destroy(){


    for(unsigned int y = 0; y < Constants::getWorldHeight(); y++){
        for(unsigned int z = 0; z < Constants::getWorldWidth(); z++){
             for(unsigned int x = 0; x < Constants::getWorldWidth(); x++){

                  getChunk(x, y, z)->destroy();

             }
        }
    }

	m_chunkShader.destroy();

}


void World::generateMesh(const std::vector<vec3>& colors, Chunk* chunk){


     m_vertices.clear();

     for(unsigned int y = 0; y < Constants::getChunkWidth(); y++){

          for(unsigned int z = 0; z < Constants::getChunkWidth(); z++){

               for(unsigned int x = 0; x < Constants::getChunkWidth(); x++){

                    uint8_t block = getBlock(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z);

                    if(block){
                         addTopFace(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z, colors[block], m_vertices);
                         addBottomFace(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z, colors[block], m_vertices);
                         addLeftFace(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z, colors[block], m_vertices);
                         addRightFace(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z, colors[block], m_vertices);
                         addFrontFace(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z, colors[block], m_vertices);
                         addBackFace(chunk->getX() + x, chunk->getY() + y, chunk->getZ() + z, colors[block], m_vertices);
                    }
               }
          }
     }

     chunk->pushData(m_vertices);
}

uint8_t World::getBlock(int x, int y, int z){

	if(!(x < 0 || x >= Constants::getChunkWidth() * Constants::getWorldWidth() || y < 0 || y >= Constants::getChunkWidth() * Constants::getWorldHeight() || z < 0 || z >= Constants::getChunkWidth() * Constants::getWorldWidth())){
		return data[(y * Constants::getChunkWidth() * Constants::getWorldWidth() * Constants::getChunkWidth() * Constants::getWorldWidth()) + (z * Constants::getChunkWidth() * Constants::getWorldWidth()) + x];
	}

	return 1;
}

void World::setBlock(int x, int y, int z, uint8_t block) {

     if(!(x < 0 || x >= Constants::getChunkWidth() * Constants::getWorldWidth() || y < 0 || y >= Constants::getChunkWidth() * Constants::getWorldHeight()|| z < 0 || z >= Constants::getChunkWidth() * Constants::getWorldWidth())){

          data[(y * Constants::getChunkWidth() * Constants::getWorldWidth() * Constants::getChunkWidth() * Constants::getWorldWidth()) + (z * Constants::getChunkWidth() * Constants::getWorldWidth()) + x] = block;

          unsigned int posX = x / Constants::getChunkWidth();
          unsigned int posY = y / Constants::getChunkWidth();
          unsigned int posZ = z / Constants::getChunkWidth();

          getChunk(posX, posY, posZ)->needsUpdate = true;

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


}

Chunk* World::getChunk(int x, int y, int z){
     if(!(x < 0 || x >= Constants::getWorldWidth() || z < 0 || z >= Constants::getWorldWidth() || y < 0 || y >= Constants::getWorldHeight()))
          return &m_chunks[(y * Constants::getWorldWidth() * Constants::getWorldWidth()) + (z * Constants::getWorldWidth()) + x];

     return nullptr;
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
