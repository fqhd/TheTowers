#pragma once

#include "ParticleQuad.hpp"
#include "Shader.hpp"
#include "Particle.hpp"
#include "Camera.hpp"
#include "TextureArray.hpp"
#include "BlockTextureHandler.hpp"
#include <vector>

class ParticleHandler {
public:


	void init(TextureArray* _array, BlockTextureHandler* _textureHandler);
	void update(float deltaTime);
	void render(Camera& camera);
	void destroy();

	void placeParticlesAroundBlock(int x, int y, int z, uint8_t _blockID);


private:

	std::vector<ParticleInstance> m_particleStructs;
	std::vector<Particle> m_particles;
	ParticleQuad m_quad;
	TextureArray* m_textureArray = nullptr;
	BlockTextureHandler* m_blockTextureHandler = nullptr;
	Shader m_shader;

};

