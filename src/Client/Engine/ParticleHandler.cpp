#include "ParticleHandler.hpp"
#include "Converter.hpp"
#include <cstring>

const float GRAVITY = 28.0f;

void ParticleHandler::init(TextureArray* _array, BlockTextureHandler* _textureHandler){
	m_blockTextureHandler = _textureHandler;
	m_textureArray = _array;
	m_quad.init();
	m_shader.load("res/shaders/particle_vertex_shader.glsl", "res/shaders/particle_fragment_shader.glsl");
}

void ParticleHandler::update(float deltaTime){
	for(unsigned int i = 0; i < m_particles.size(); i++){
		m_particles[i].velocity.y -= GRAVITY * deltaTime;
		m_particles[i].position += m_particles[i].velocity * deltaTime;
		m_particles[i].lifeLength -= deltaTime;
		if(m_particles[i].lifeLength <= 0.0f){
			m_particles[i] = m_particles.back();
			m_particles.pop_back();
		}
	}
}

void ParticleHandler::render(Camera& camera){
	// Gathering particle data and sending it to GPU
	m_particleInstances.resize(0);
	for(unsigned int i = 0; i < m_particles.size(); i++){
		m_particleInstances.emplace_back(m_particles[i].position, m_particles[i].textureIndex, m_particles[i].size);
	}
	m_quad.pushData(m_particleInstances.data(), m_particleInstances.size() * sizeof(ParticleInstance));

	
	// Rendering particles
	m_shader.bind();
	// Since we are rendering the particles as GL_POINTS, this uniform variable is necessary 
	// in order to scale the particles based on the width of the screen. Otherwise the particles
	// will have a fixed size regardless of screen size.
	m_shader.loadUniform("screenWidth", InputManager::getWindowSize().x);
	m_shader.loadUniform("projection", camera.getProjectionMatrix());
	m_shader.loadUniform("view", camera.getViewMatrix());

	m_textureArray->bind();

	glDisable(GL_CULL_FACE);
	m_quad.render(m_particleInstances.size());
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
	BlockTexture b = m_blockTextureHandler->getTextureFromBlockID(_blockID);
	for(unsigned int i = 0; i < PARTICLES_PER_DROP; i++) {
		math::vec3 pos(x + math::random(), y + math::random(), z + math::random());
		math::vec3 direction = pos - (math::vec3(x, y, z) + math::vec3(0.5f, 0.0f, 0.5f));
		math::vec3 velocity = math::vec3(direction.x * 3.0f, direction.y * 4.0f, direction.z * 3.0f);
		m_particles.emplace_back(Particle(pos, velocity, 1.0f, getRandom(b.bot, b.side, b.top), 100.0f + math::random() * 100.0f));
	}
}

void ParticleHandler::destroy(){
	m_quad.destroy();
	m_shader.destroy();
}
