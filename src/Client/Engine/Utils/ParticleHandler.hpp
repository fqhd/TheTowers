#pragma once

#include "ParticleQuad.hpp"
#include "ParticleShader.hpp"
#include "Particle.hpp"
#include "Camera.hpp"
#include <vector>

class ParticleHandler {
public:

	void init();
	void update(float deltaTime);
	void render(Camera& camera);
	void destroy();

	void placeParticlesAroundBlock(int x, int y, int z);

	std::vector<Particle> particles;


private:

	ParticleQuad m_quad;
	ParticleShader m_shader;

};

#endif
