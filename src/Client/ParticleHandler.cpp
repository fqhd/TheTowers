#include "ParticleHandler.hpp"
#include "Converter.hpp"
#include <cstring>

const float GRAVITY = 18.0f;


void ParticleHandler::init(TextureArray* _array, BlockTextureHandler* _textureHandler){
	m_blockTextureHandler = _textureHandler;
	m_textureArray = _array;
	m_quad.init();
	m_shader.load("res/shaders/particle_vertex_shader.glsl", "res/shaders/particle_fragment_shader.glsl");
	m_particles = new Particle[MAX_PARTICLES];
}

void ParticleHandler::update(float deltaTime){
	for(unsigned int i = 0; i < m_currNumParticles; i++){
		m_particles[i].velocity.y -= GRAVITY * deltaTime;
		m_particles[i].position += m_particles[i].velocity * deltaTime;
		m_particles[i].lifeLength -= deltaTime;
		if(m_particles[i].lifeLength <= 0.0f){
			memcpy(&m_particles[i], &m_particles[m_currNumParticles - 1], sizeof(Particle));
			m_currNumParticles--;
		}
	}
}

void ParticleHandler::render(Camera& camera){
	// Gathering particle data and sending it to GPU
	m_particleStructs.resize(0);
	for(unsigned int i = 0; i < m_currNumParticles; i++){
		m_particleStructs.emplace_back(m_particles[i].position, m_particles[i].textureIndex);
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

unsigned int getRandom(uint8_t a, uint8_t b, uint8_t c){
	int r = rand()%3;
	if(r == 2){
		return a;
	}else if(r == 1){
		return b;
	}
	return c;
}

void ParticleHandler::placeParticlesAroundBlock(int x, int y, int z, uint8_t _blockID){
	if(m_currNumParticles == MAX_PARTICLES) return;
	BlockTexture b = m_blockTextureHandler->getTextureFromBlockID(_blockID);
	for(unsigned int i = 0; i < PARTICLES_PER_DROP; i++){
		math::vec3 pos(x + math::random(), y + math::random(), z + math::random());
		math::vec3 velocity((math::random() - 0.5f) * 3.0f, math::random() * 5, (math::random() - 0.5f) * 3.0f);
		m_particles[m_currNumParticles + i] = Particle(pos, velocity, 1.0f, getRandom(b.top, b.side, b.bot));
	}
	m_currNumParticles += PARTICLES_PER_DROP;
}

void ParticleHandler::destroy(){
	m_quad.destroy();
	m_shader.destroy();
}
