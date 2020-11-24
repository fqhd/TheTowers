#include "World.hpp"

void World::init(uint8_t* d){

     data = d;

     for(unsigned int y = 0; y < WORLD_HEIGHT; y++){
          for(unsigned int z = 0; z < WORLD_SIZE; z++){
               for(unsigned int x = 0; x < WORLD_SIZE; x++){

                    chunks[y][z][x].init(x * CHUNK_WIDTH, y * CHUNK_WIDTH, z * CHUNK_WIDTH);

               }
          }
     }

     m_chunkShader.loadShader("res/shaders/chunkVertex.glsl", "res/shaders/chunkFragment.glsl");
     m_chunkShader.getUniformLocations();
}

void World::render(Camera& camera, const std::vector<vec3>& colors, float range){

     m_chunkShader.bind();
     m_chunkShader.loadMatrix(camera.getProjectionMatrix() * camera.getViewMatrix());

     for(unsigned int i = 0; i < WORLD_HEIGHT; i++){
          for(unsigned int j = 0; j < WORLD_SIZE; j++){
               for(unsigned int k = 0; k < WORLD_SIZE; k++){

                    if(chunks[i][j][k].needsUpdate){
                         generateMesh(colors, chunks[i][j][k]);
                         chunks[i][j][k].needsUpdate = false;
                    }



                    if(Utils::isInRange(camera.getPosition(), glm::vec3(chunks[i][j][k].getX() + CHUNK_WIDTH / 2,
                    chunks[i][j][k].getY() + CHUNK_WIDTH / 2, chunks[i][j][k].getZ() + CHUNK_WIDTH / 2), range) && chunks[i][j][k].getNumVertices()) {
                         chunks[i][j][k].render();
                    }

               }
          }
     }



     m_chunkShader.unbind();

}

void World::destroy(){

    for(unsigned int i = 0; i < WORLD_HEIGHT; i++){
        for(unsigned int j = 0; j < WORLD_SIZE; j++){
             for(unsigned int k = 0; k < WORLD_SIZE; k++){
                  chunks[i][j][k].destroy();
             }
        }
    }

	m_chunkShader.destroy();

}


void World::generateMesh(const std::vector<vec3>& colors, Chunk& chunk){


     m_vertices.clear();

     for(unsigned int y = 0; y < CHUNK_WIDTH; y++){

          for(unsigned int z = 0; z < CHUNK_WIDTH; z++){

               for(unsigned int x = 0; x < CHUNK_WIDTH; x++){

                    uint8_t block = getBlock(chunk.getX() + x, chunk.getY() + y, chunk.getZ() + z);

                    if(block){
                         addTopFace(chunk.getX() + x, chunk.getY() + y, chunk.getZ() + z, colors[block], m_vertices);
                         addBottomFace(chunk.getX() + x, chunk.getY() + y, chunk.getZ() + z, colors[block], m_vertices);
                         addLeftFace(chunk.getX() + x, chunk.getY() + y, chunk.getZ() + z, colors[block], m_vertices);
                         addRightFace(chunk.getX() + x, chunk.getY() + y, chunk.getZ() + z, colors[block], m_vertices);
                         addFrontFace(chunk.getX() + x, chunk.getY() + y, chunk.getZ() + z, colors[block], m_vertices);
                         addBackFace(chunk.getX() + x, chunk.getY() + y, chunk.getZ() + z, colors[block], m_vertices);
                    }
               }
          }
     }

     chunk.pushData(m_vertices);
}

uint8_t World::getBlock(int x, int y, int z){

	if(!(x < 0 || x >= CHUNK_WIDTH * WORLD_SIZE || y < 0 || y >= CHUNK_WIDTH * WORLD_HEIGHT || z < 0 || z >= CHUNK_WIDTH * WORLD_SIZE)){
		return data[(y * CHUNK_WIDTH * WORLD_SIZE * CHUNK_WIDTH * WORLD_SIZE) + (z * CHUNK_WIDTH * WORLD_SIZE) + x];
	}

	return 1;
}

void World::setBlock(int x, int y, int z, uint8_t block) {

     if(!(x < 0 || x >= CHUNK_WIDTH * WORLD_SIZE || y < 0 || y >= CHUNK_WIDTH * WORLD_HEIGHT|| z < 0 || z >= CHUNK_WIDTH * WORLD_SIZE)){

          data[(y * CHUNK_WIDTH * WORLD_SIZE * CHUNK_WIDTH * WORLD_SIZE) + (z * CHUNK_WIDTH * WORLD_SIZE) + x] = block;

          unsigned int posX = x / CHUNK_WIDTH;
          unsigned int posY = y / CHUNK_WIDTH;
          unsigned int posZ = z / CHUNK_WIDTH;

          chunks[posY][posZ][posX].needsUpdate = true;

		if(x % CHUNK_WIDTH == 0){
			Chunk* chunk = getChunk(posX - 1, posY, posZ);
			if(chunk) chunk->needsUpdate = true;
		}
		if((x + 1) % CHUNK_WIDTH == 0){
			Chunk* chunk = getChunk(posX + 1, posY, posZ);
			if(chunk) chunk->needsUpdate = true;
		}
          if(z % CHUNK_WIDTH == 0){
			Chunk* chunk = getChunk(posX, posY, posZ - 1);
			if(chunk) chunk->needsUpdate = true;
		}
		if((z + 1) % CHUNK_WIDTH == 0){
			Chunk* chunk = getChunk(posX, posY, posZ + 1);
			if(chunk) chunk->needsUpdate = true;
		}
          if(y % CHUNK_WIDTH == 0){
			Chunk* chunk = getChunk(posX, posY - 1, posZ);
			if(chunk) chunk->needsUpdate = true;
		}
		if((y + 1) % CHUNK_WIDTH == 0){
			Chunk* chunk = getChunk(posX, posY + 1, posZ);
			if(chunk) chunk->needsUpdate = true;
		}



     }


}

Chunk* World::getChunk(int x, int y, int z){
     if(!(x < 0 || x >= WORLD_SIZE || z < 0 || z >= WORLD_SIZE || y < 0 || y >= WORLD_HEIGHT))
          return &chunks[y][z][x];

     return nullptr;
}

void World::addTopFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){

	if(getBlock(x, y + 1, z)) return;

	float of = 1.0f;

	of = (getBlock(x, y + 1, z - 1) || getBlock(x - 1, y + 1, z - 1) || getBlock(x - 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y + 1, z) || getBlock(x - 1, y + 1, z + 1) || getBlock(x, y + 1, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z + 1) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z - 1) || getBlock(x - 1, y + 1, z - 1) || getBlock(x - 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z + 1) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z - 1) || getBlock(x + 1, y + 1, z - 1) || getBlock(x + 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

}

void World::addBottomFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x, y - 1, z)) return;

	float of = 1.0f;

	of = (getBlock(x, y - 1, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x - 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z + 1) || getBlock(x + 1, y - 1, z + 1) || getBlock(x + 1, y- 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y- 1, z) || getBlock(x - 1, y- 1, z + 1) || getBlock(x, y- 1, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x - 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z - 1) || getBlock(x + 1, y - 1, z - 1) || getBlock(x + 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z + 1) || getBlock(x + 1, y - 1, z + 1) || getBlock(x + 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

}

void World::addRightFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x - 1, y, z)) return;

	float of = 1.0f;

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x - 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y + 1, z) || getBlock(x - 1, y + 1, z + 1) || getBlock(x - 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y + 1, z - 1) || getBlock(x - 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x - 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z + 1) || getBlock(x - 1, y - 1, z + 1) || getBlock(x - 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y + 1, z) || getBlock(x - 1, y + 1, z + 1) || getBlock(x - 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

}

void World::addLeftFace(int x, int  y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x + 1, y, z)) return;

	float of = 1.0f;

	of = (getBlock(x + 1, y, z - 1) || getBlock(x + 1, y - 1, z - 1) || getBlock(x + 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y, z - 1) || getBlock(x + 1, y + 1, z - 1) || getBlock(x + 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y + 1, z) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y, z - 1) || getBlock(x + 1, y - 1, z - 1) || getBlock(x + 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y + 1, z) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y, z + 1) || getBlock(x + 1, y - 1, z + 1) || getBlock(x + 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

}

void World::addFrontFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x, y, z - 1)) return;

	float of = 1.0f;

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x, y - 1, z - 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y + 1, z - 1) || getBlock(x, y + 1, z - 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z - 1) || getBlock(x + 1, y + 1, z - 1) || getBlock(x + 1, y, z - 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x, y - 1, z - 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z - 1) || getBlock(x + 1, y + 1, z - 1) || getBlock(x + 1, y, z - 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z - 1) || getBlock(x + 1, y - 1, z - 1) || getBlock(x + 1, y, z - 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));
}

void World::addBackFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x, y, z + 1)) return;

	float of = 1.0f;

	of = (getBlock(x - 1, y, z + 1) || getBlock(x - 1, y - 1, z + 1) || getBlock(x, y - 1, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z + 1) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z + 1) || getBlock(x - 1, y + 1, z + 1) || getBlock(x, y + 1, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z + 1) || getBlock(x - 1, y - 1, z + 1) || getBlock(x, y - 1, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z + 1) || getBlock(x + 1, y - 1, z + 1) || getBlock(x + 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z + 1) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));


}
