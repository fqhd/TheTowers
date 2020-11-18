#include "World.hpp"

void World::init(){

    m_data = new char[CHUNK_SIZE * WORLD_SIZE * WORLD_SIZE];

    generateWorld();

    for(unsigned int z = 0; z < WORLD_SIZE; z++){
        for(unsigned int x = 0; x < WORLD_SIZE; x++){

            chunks[z][x].init(x * CHUNK_WIDTH, z * CHUNK_WIDTH);

        }
    }

	m_chunkShader.loadShader("res/shaders/chunkVertex.glsl", "res/shaders/chunkFragment.glsl");
	m_chunkShader.getUniformLocations();

}

void World::render(Camera& camera, const std::vector<vec3>& colors){

     m_chunkShader.bind();
     m_chunkShader.loadMatrix(camera.getProjectionMatrix() * camera.getViewMatrix());

     for(unsigned int i = 0; i < WORLD_SIZE; i++){
          for(unsigned int j = 0; j < WORLD_SIZE; j++){

               if(chunks[i][j].needsUpdate){
                    generateMesh(colors, chunks[i][j]);
                    chunks[i][j].needsUpdate = false;
               }

               chunks[i][j].render();

          }
     }



     m_chunkShader.unbind();

}

void World::destroy(){

    for(unsigned int i = 0; i < WORLD_SIZE; i++){
        for(unsigned int j = 0; j < WORLD_SIZE; j++){

            chunks[i][j].destroy();

        }
    }

	m_chunkShader.destroy();

}


void World::generateMesh(const std::vector<vec3>& colors, Chunk& chunk){


	m_vertices.clear();

    for(unsigned int y = 0; y < CHUNK_WIDTH; y++){

        for(unsigned int z = 0; z < CHUNK_WIDTH; z++){

            for(unsigned int x = 0; x < CHUNK_WIDTH; x++){

                char block = getBlock(chunk.getX() + x, y, chunk.getZ() + z);

				if(block){
					addTopFace(chunk.getX() + x, y, chunk.getZ() + z, colors[block - 1], m_vertices);
					addBottomFace(chunk.getX() + x, y, chunk.getZ() + z, colors[block - 1], m_vertices);
					addLeftFace(chunk.getX() + x, y, chunk.getZ() + z, colors[block - 1], m_vertices);
					addRightFace(chunk.getX() + x, y, chunk.getZ() + z, colors[block - 1], m_vertices);
					addFrontFace(chunk.getX() + x, y, chunk.getZ() + z, colors[block - 1], m_vertices);
					addBackFace(chunk.getX() + x, y, chunk.getZ() + z, colors[block - 1], m_vertices);
				}
            }
        }
    }

    chunk.pushData(m_vertices);

}


void World::generateWorld(){

    for(unsigned int i = 0; i < CHUNK_SIZE * WORLD_SIZE * WORLD_SIZE; i++){
		m_data[i] = 0;
	}

	for(unsigned int x = 0; x < CHUNK_WIDTH * WORLD_SIZE; x++){
		for(unsigned int z = 0; z < CHUNK_WIDTH * WORLD_SIZE; z++){

			float percentage = (glm::perlin(glm::vec2(x * 0.25f / CHUNK_WIDTH * WORLD_SIZE, z * 0.25f / CHUNK_WIDTH * WORLD_SIZE)) + 1) / 2.0f;

			int height = CHUNK_WIDTH * percentage;

			for(unsigned int y = 0; y < height; y++){
				m_data[(y * CHUNK_WIDTH * WORLD_SIZE * CHUNK_WIDTH * WORLD_SIZE) + (z * CHUNK_WIDTH * WORLD_SIZE) + x] = y + 100;
			}

		}
	}


}

char World::getBlock(int x, int y, int z){

	if(!(x < 0 || x >= CHUNK_WIDTH * WORLD_SIZE || y < 0 || y >= CHUNK_WIDTH || z < 0 || z >= CHUNK_WIDTH * WORLD_SIZE)){
		return m_data[(y * CHUNK_WIDTH * WORLD_SIZE * CHUNK_WIDTH * WORLD_SIZE) + (z * CHUNK_WIDTH * WORLD_SIZE) + x];
	}

	return 1;
}

void World::setBlock(int x, int y, int z, char block){

     if(!(x < 0 || x >= CHUNK_WIDTH * WORLD_SIZE || y < 0 || y >= CHUNK_WIDTH || z < 0 || z >= CHUNK_WIDTH * WORLD_SIZE)){

          m_data[(y * CHUNK_WIDTH * WORLD_SIZE * CHUNK_WIDTH * WORLD_SIZE) + (z * CHUNK_WIDTH * WORLD_SIZE) + x] = block;

          unsigned int posX = x / CHUNK_WIDTH;
          unsigned int posZ = z / CHUNK_WIDTH;

          chunks[posZ][posX].needsUpdate = true;

		if(x % CHUNK_WIDTH == 0){
			Chunk* chunk = getChunk(posX - 1, posZ);
			if(chunk) chunk->needsUpdate = true;
		}
		if((x + 1) % CHUNK_WIDTH == 0){
			Chunk* chunk = getChunk(posX + 1, posZ);
			if(chunk) chunk->needsUpdate = true;
		}
		if(z % CHUNK_WIDTH == 0){
			Chunk* chunk = getChunk(posX, posZ - 1);
			if(chunk) chunk->needsUpdate = true;
		}
		if((z + 1) % CHUNK_WIDTH == 0){
			Chunk* chunk = getChunk(posX, posZ + 1);
			if(chunk) chunk->needsUpdate = true;
		}



     }


}

Chunk* World::getChunk(int x, int z){
     if(!(x < 0 || x >= WORLD_SIZE || z < 0 || z >= WORLD_SIZE))
          return &chunks[z][x];

     return nullptr;
}

void World::addTopFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){

	if(getBlock(x, y + 1, z)) return;

	float of = 1.0f;

	of = (getBlock(x, y + 1, z - 1) || getBlock(x - 1, y + 1, z - 1) || getBlock(x - 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y + 1, z) || getBlock(x - 1, y + 1, z + 1) || getBlock(x, y + 1, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z + 1) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z - 1) || getBlock(x - 1, y + 1, z - 1) || getBlock(x - 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z + 1) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z - 1) || getBlock(x + 1, y + 1, z - 1) || getBlock(x + 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

}

void World::addBottomFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x, y - 1, z)) return;

	float of = 1.0f;

	of = (getBlock(x, y - 1, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x - 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z + 1) || getBlock(x + 1, y - 1, z + 1) || getBlock(x + 1, y- 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y- 1, z) || getBlock(x - 1, y- 1, z + 1) || getBlock(x, y- 1, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x - 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z - 1) || getBlock(x + 1, y - 1, z - 1) || getBlock(x + 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z + 1) || getBlock(x + 1, y - 1, z + 1) || getBlock(x + 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

}

void World::addRightFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x - 1, y, z)) return;

	float of = 1.0f;

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x - 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y + 1, z) || getBlock(x - 1, y + 1, z + 1) || getBlock(x - 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y + 1, z - 1) || getBlock(x - 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x - 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z + 1) || getBlock(x - 1, y - 1, z + 1) || getBlock(x - 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y + 1, z) || getBlock(x - 1, y + 1, z + 1) || getBlock(x - 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

}

void World::addLeftFace(int x, int  y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x + 1, y, z)) return;

	float of = 1.0f;

	of = (getBlock(x + 1, y, z - 1) || getBlock(x + 1, y - 1, z - 1) || getBlock(x + 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y, z - 1) || getBlock(x + 1, y + 1, z - 1) || getBlock(x + 1, y + 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y + 1, z) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y, z - 1) || getBlock(x + 1, y - 1, z - 1) || getBlock(x + 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y + 1, z) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x + 1, y, z + 1) || getBlock(x + 1, y - 1, z + 1) || getBlock(x + 1, y - 1, z)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

}

void World::addFrontFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x, y, z - 1)) return;

	float of = 1.0f;

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x, y - 1, z - 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y + 1, z - 1) || getBlock(x, y + 1, z - 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z - 1) || getBlock(x + 1, y + 1, z - 1) || getBlock(x + 1, y, z - 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z - 1) || getBlock(x - 1, y - 1, z - 1) || getBlock(x, y - 1, z - 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z - 1) || getBlock(x + 1, y + 1, z - 1) || getBlock(x + 1, y, z - 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y + 1, z), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z - 1) || getBlock(x + 1, y - 1, z - 1) || getBlock(x + 1, y, z - 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y, z), vec3(color.r * of, color.g * of, color.b * of));
}

void World::addBackFace(int x, int y, int z, const vec3& color, std::vector<Vertex>& vertices){
	if(getBlock(x, y, z + 1)) return;

	float of = 1.0f;

	of = (getBlock(x - 1, y, z + 1) || getBlock(x - 1, y - 1, z + 1) || getBlock(x, y - 1, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z + 1) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z + 1) || getBlock(x - 1, y + 1, z + 1) || getBlock(x, y + 1, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x - 1, y, z + 1) || getBlock(x - 1, y - 1, z + 1) || getBlock(x, y - 1, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y - 1, z + 1) || getBlock(x + 1, y - 1, z + 1) || getBlock(x + 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y, z + 1), vec3(color.r * of, color.g * of, color.b * of));

	of = (getBlock(x, y + 1, z + 1) || getBlock(x + 1, y + 1, z + 1) || getBlock(x + 1, y, z + 1)) ? OCCLUSION_FACTOR : 1.0f;
	vertices.emplace_back(vec3(x + 1, y + 1, z + 1), vec3(color.r * of, color.g * of, color.b * of));


}
