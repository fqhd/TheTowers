#include "ParticleHandler.hpp"

const unsigned int NUM_PARTICLES = 50;

void ParticleHandler::init(){
	m_quad.init();
	m_shader.load("res/shaders/particle_vertex_shader.glsl", "res/shaders/particle_fragment_shader.glsl");
}

void ParticleHandler::update(float deltaTime){
	for(auto& i : particles){
		if(i.update(deltaTime)){
			i = particles.back();
			particles.pop_back();
		}
	}
}

void ParticleHandler::render(Camera& camera){

	std::vector<math::mat4> matrices;

	// for(auto& i : particles){
		// math::mat4 posMatrix = math::translate(i.getPosition());
		// posMatrix[0][0] = camera.getViewMatrix().m[0][0];
		// posMatrix[0][1] = camera.getViewMatrix().m[1][0];
		// posMatrix[0][2] = camera.getViewMatrix().m[2][0];
		// posMatrix[1][0] = camera.getViewMatrix().m[0][1];
		// posMatrix[1][1] = camera.getViewMatrix().m[1][1];
		// posMatrix[1][2] = camera.getViewMatrix().m[2][1];
		// posMatrix[2][0] = camera.getViewMatrix().m[0][2];
		// posMatrix[2][1] = camera.getViewMatrix().m[1][2];
		// posMatrix[2][2] = camera.getViewMatrix().m[2][2];
		// math::mat4 rotMatrix = math::rotate(i.getRotation(), math::vec3(0, 0, 1));
		// math::mat4 scaleMatrix = math::scale(math::vec3(i.getScale(), i.getScale(), i.getScale()));
		// math::mat4 modelMatrix = posMatrix * rotMatrix * scaleMatrix;

		// math::mat4 matrix = camera.getViewMatrix() * modelMatrix;

		// matrices.push_back(matrix);
	// }

	m_shader.bind();
	glDisable(GL_CULL_FACE);
	m_quad.bind();

	m_shader.loadUniform("projection", camera.getProjectionMatrix());

	m_quad.pushMatrices(matrices);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, matrices.size());

	m_quad.unbind();
	glEnable(GL_CULL_FACE);
	m_shader.unbind();

}

void ParticleHandler::placeParticlesAroundBlock(int x, int y, int z){
	for(unsigned int j = 0; j < NUM_PARTICLES; j++){
		// particles.emplace_back(color, math::vec3(x, y, z) + math::vec3((rand()%11) / 10.0f, (rand()%11)/10.0f, (rand()%11)/10.0f), math::vec3((rand()%10) - 5, 10, (rand()%10) - 5) * 0.20f, 1.25f, 0.0f, 0.125f);
	}
}


void ParticleHandler::destroy(){
	particles.clear();
	m_quad.destroy();
	m_shader.destroy();
}
