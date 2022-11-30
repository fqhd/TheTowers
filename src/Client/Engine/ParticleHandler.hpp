#pragma once

#include "ParticleQuad.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "TextureArray.hpp"
#include "BlockTextureHandler.hpp"
#include <vector>

const unsigned int PARTICLES_PER_DROP = 50;

struct Particle {
	Particle(){
		textureIndex = 0;
		lifeLength = 0.0f;
		velocity = glm::vec3(0.0f);
		position = glm::vec3(0.0f);
	}
	Particle(const glm::vec3& p, const glm::vec3& v, float l, float i, float _size){
		position = p;
		velocity = v;
		lifeLength = l;
		textureIndex = i;
		size = _size;
	}
	glm::vec3 position;
	glm::vec3 velocity;
	float lifeLength;
	float size;
	unsigned int textureIndex;
};

struct ParticleInstance {
	ParticleInstance(){}
	ParticleInstance(const glm::vec3& p, unsigned int i, float _size){
		pos = p;
		tindex = i;
		size = _size;
	}
	glm::vec3 pos;
	unsigned int tindex;
	float size;
};

class ParticleHandler {
public:

	void init(TextureArray* _array, BlockTextureHandler* _textureHandler);
	void update(float deltaTime);
	void render(Camera& camera);
	void destroy();

	void placeParticlesAroundBlock(int x, int y, int z, uint8_t _blockID);

private:

	std::vector<Particle> m_particles;
	std::vector<ParticleInstance> m_particleInstances;
	ParticleQuad m_quad;
	TextureArray* m_textureArray = nullptr;
	BlockTextureHandler* m_blockTextureHandler = nullptr;
	Shader m_shader;

};

