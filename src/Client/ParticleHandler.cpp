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
	m_matrices.resize(0);
	m_textureIndices.resize(0);
	for(unsigned int i = 0; i < m_particles.size(); i++){
		math::mat4 matrix;
		matrix.setIdentity();
		math::translate(m_particles[i].getPosition(), matrix, matrix);
		matrix.m[0][0] = camera.getViewMatrix().m[0][0];
		matrix.m[0][1] = camera.getViewMatrix().m[1][0];
		matrix.m[0][2] = camera.getViewMatrix().m[2][0];
		matrix.m[1][0] = camera.getViewMatrix().m[0][1];
		matrix.m[1][1] = camera.getViewMatrix().m[1][1];
		matrix.m[1][2] = camera.getViewMatrix().m[2][1];
		matrix.m[2][0] = camera.getViewMatrix().m[0][2];
		matrix.m[2][1] = camera.getViewMatrix().m[1][2];
		matrix.m[2][2] = camera.getViewMatrix().m[2][2];
		math::rotate(m_particles[i].getRotation(), math::vec3(0, 0, 1), matrix, matrix);
		math::scale(math::vec3(m_particles[i].getScale()), matrix, matrix);

		m_matrices.push_back(matrix);
		m_textureIndices.push_back(m_particles[i].getTextureIndex());
	}

	m_quad.pushMatrices(m_matrices.data(), m_matrices.size());
	m_quad.pushTextureIndices(m_textureIndices.data(), m_textureIndices.size());

	m_shader.bind();
	m_shader.loadUniform("projection", camera.getProjectionMatrix());
	m_shader.loadUniform("view", camera.getViewMatrix());

	m_textureArray->bind();

	glDisable(GL_CULL_FACE);
	m_quad.render(m_matrices.size());
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
