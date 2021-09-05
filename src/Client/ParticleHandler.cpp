#include "ParticleHandler.hpp"
#include "Converter.hpp"

const unsigned int NUM_PARTICLES = 50;

void ParticleHandler::init(TextureArray* _array, BlockTextureHandler* _textureHandler){
	m_blockTextureHandler = _textureHandler;
	m_textureArray = _array;
	m_quad.init();
	m_shader.load("res/shaders/particle_vertex_shader.glsl", "res/shaders/particle_fragment_shader.glsl");
}

void ParticleHandler::update(float deltaTime){
	for(auto& i : m_particles){
		if(i.update(deltaTime)){
			i = m_particles.back();
			m_particles.pop_back();
		}
	}
}

void ParticleHandler::render(Camera& camera){
	// Gathering particle data and sending it to GPU
	m_particleStructs.resize(0);
	for(auto& i : m_particles){
		m_particleStructs.emplace_back(i.getPosition(), i.getTextureIndex());
	}
	m_quad.pushData(m_particleStructs.data(), m_particleStructs.size());



	// Rendering particles
	m_shader.bind();
	m_shader.loadUniform("projection", camera.getProjectionMatrix());
	m_shader.loadUniform("view", camera.getViewMatrix());

	m_textureArray->bind();

	glDisable(GL_CULL_FACE);
	m_quad.render(m_particleStructs.size());
	glEnable(GL_CULL_FACE);

	m_textureArray->unbind();

	m_shader.unbind();
}

unsigned int getRandom(uint16_t a, uint16_t b, uint16_t c){
	int r = rand()%3;
	if(r == 2){
		return a;
	}else if(r == 1){
		return b;
	}
	return c;
}

void ParticleHandler::placeParticlesAroundBlock(int x, int y, int z, uint8_t _blockID){
	for(unsigned int j = 0; j < NUM_PARTICLES; j++){
		math::vec3 pos(x + math::random(), y + math::random(), z + math::random());
		math::vec3 velocity((math::random() - 0.5f) * 3.0f, math::random() * 5, (math::random() - 0.5f) * 3.0f);
		float scale = 0.1f + math::random() * 0.1;
		BlockTexture b = m_blockTextureHandler->getTextureFromBlockID(_blockID);
		m_particles.push_back(Particle(pos, velocity, 1.0f, 0.0f, scale, getRandom(b.top, b.side, b.bot)));
	}
}

void ParticleHandler::destroy(){
	m_quad.destroy();
	m_shader.destroy();
}
