#pragma once

#include "ParticleQuad.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "TextureArray.hpp"
#include "BlockTextureHandler.hpp"
#include <vector>

const unsigned int MAX_PARTICLES = 10000;
const unsigned int PARTICLES_PER_DROP = 100;

struct Particle {
	Particle(){
		textureIndex = 0;
		lifeLength = 0.0f;
		velocity = math::vec3(0.0f);
		position = math::vec3(0.0f);
	}
	Particle(const math::vec3& p, const math::vec3& v, float l, float i, float _size){
		position = p;
		velocity = v;
		lifeLength = l;
		textureIndex = i;
		size = _size;
	}
	math::vec3 position;
	math::vec3 velocity;
	float lifeLength;
	float size;
	unsigned int textureIndex;
};

struct ParticleInstance {
	ParticleInstance(){}
	ParticleInstance(const math::vec3& p, unsigned int i, float _size){
		pos = p;
		tindex = i;
		size = _size;
	}
	math::vec3 pos;
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

	unsigned int m_currNumParticles = 0;
	Particle* m_particles = nullptr;
	std::vector<ParticleInstance> m_particleStructs;
	ParticleQuad m_quad;
	TextureArray* m_textureArray = nullptr;
	BlockTextureHandler* m_blockTextureHandler = nullptr;
	Shader m_shader;

};

