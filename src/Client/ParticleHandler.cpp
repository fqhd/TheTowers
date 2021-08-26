#include "ParticleHandler.hpp"
#include "Converter.hpp"

const unsigned int NUM_PARTICLES = 50;

void ParticleHandler::init(TextureArray* _array){
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
	m_uvQuads.resize(0);

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
		m_uvQuads.push_back(math::vec4(0, 0, 1, 1));
	}

	m_quad.pushMatrices(m_matrices);
	m_quad.pushUVQuads(m_uvQuads);

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

void ParticleHandler::placeParticlesAroundBlock(int x, int y, int z, uint8_t _blockID){
	for(unsigned int j = 0; j < NUM_PARTICLES; j++){
		float time = 0.5f + (rand() % 100) / 200.0f;
		float scale = 0.125f + (rand() % 100) / 800.0f;
		m_particles.emplace_back(math::vec3(x, y, z) + math::vec3((rand()%11) / 10.0f, (rand()%11)/10.0f, (rand()%11)/10.0f), math::vec3((rand()%10) - 5, 10, (rand()%10) - 5) * 0.20f, time, 0.0f, scale, TextureIndex::GRASS_TOP);
	}
}

void ParticleHandler::destroy(){
	m_quad.destroy();
	m_shader.destroy();
}
