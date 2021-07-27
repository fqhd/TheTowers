#include "ParticleHandler.hpp"

const unsigned int NUM_PARTICLES = 50000;

void ParticleHandler::init(){
	m_quad.init();
	m_shader.load("res/shaders/particle_vertex_shader.glsl", "res/shaders/particle_fragment_shader.glsl");
	m_particleTexture.loadFromFile("res/textures/particle_texture.png");
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
	m_uvs.resize(0);
	
	for(auto& i : m_particles){
		math::mat4 matrix;
		matrix.setIdentity();
		math::translate(i.getPosition(), matrix, matrix);
		matrix.m[0][0] = camera.getViewMatrix().m[0][0];
		matrix.m[0][1] = camera.getViewMatrix().m[1][0];
		matrix.m[0][2] = camera.getViewMatrix().m[2][0];
		matrix.m[1][0] = camera.getViewMatrix().m[0][1];
		matrix.m[1][1] = camera.getViewMatrix().m[1][1];
		matrix.m[1][2] = camera.getViewMatrix().m[2][1];
		matrix.m[2][0] = camera.getViewMatrix().m[0][2];
		matrix.m[2][1] = camera.getViewMatrix().m[1][2];
		matrix.m[2][2] = camera.getViewMatrix().m[2][2];
		math::rotate(i.getRotation(), math::vec3(0, 0, 1), matrix, matrix);
		math::scale(math::vec3(i.getScale()), matrix, matrix);

		m_matrices.push_back(matrix);
		addUVQuadToUVList(m_uvs, m_particleTexture.getUVQuad(i.getParticleID()));
	}

	m_quad.pushMatrices(m_matrices);
	m_quad.pushUVs(m_uvs);

	m_shader.bind();
	m_shader.loadUniform("projection", camera.getProjectionMatrix());
	m_shader.loadUniform("view", camera.getViewMatrix());

	m_particleTexture.bind();

	glDisable(GL_CULL_FACE);
	m_quad.render(m_matrices.size());
	glEnable(GL_CULL_FACE);

	m_particleTexture.unbind();

	m_shader.unbind();
}

void ParticleHandler::placeParticlesAroundBlock(int x, int y, int z){
	for(unsigned int j = 0; j < NUM_PARTICLES; j++){
		float time = 0.5f + (rand() % 100) / 200.0f;
		float scale = 0.125f + (rand() % 100) / 800.0f;
		m_particles.emplace_back(math::vec3(x, y, z) + math::vec3((rand()%11) / 10.0f, (rand()%11)/10.0f, (rand()%11)/10.0f), math::vec3((rand()%10) - 5, 10, (rand()%10) - 5) * 0.20f, time, 0.0f, scale, 0);
	}
}

void ParticleHandler::destroy(){
	m_particles.clear();
	m_quad.destroy();
	m_shader.destroy();
	m_particleTexture.destroy();
}

void ParticleHandler::addUVQuadToUVList(std::vector<math::vec2>& _uvs, const math::vec4& _quad){
	_uvs.emplace_back(_quad.x, _quad.y);
	_uvs.emplace_back(_quad.x, _quad.y + _quad.w);
	_uvs.emplace_back(_quad.x + _quad.z, _quad.y + _quad.w);
	_uvs.emplace_back(_quad.x, _quad.y);
	_uvs.emplace_back(_quad.x + _quad.z, _quad.y + _quad.w);
	_uvs.emplace_back(_quad.x + _quad.z, _quad.y);
}
