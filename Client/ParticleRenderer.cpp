#include "ParticleRenderer.hpp"
#include "Constants.hpp"


void ParticleRenderer::init(){
    m_quad.init();
    m_shader.loadShader("res/shaders/particleVertex.glsl", "res/shaders/particleFragment.glsl");
    m_shader.getUniformLocations();
}

void ParticleRenderer::update(float deltaTime){
    for(auto& i : particles){
        if(i.update(deltaTime)){
             i = particles.back();
             particles.pop_back();
        }
    }
}

void ParticleRenderer::render(Camera& camera){


    std::vector<glm::mat4> matrices;
    std::vector<vec3> colors;

    for(auto& i : particles){
        glm::mat4 posMatrix = glm::translate(i.getPosition());
        posMatrix[0][0] = camera.getViewMatrix()[0][0];
        posMatrix[0][1] = camera.getViewMatrix()[1][0];
        posMatrix[0][2] = camera.getViewMatrix()[2][0];
        posMatrix[1][0] = camera.getViewMatrix()[0][1];
        posMatrix[1][1] = camera.getViewMatrix()[1][1];
        posMatrix[1][2] = camera.getViewMatrix()[2][1];
        posMatrix[2][0] = camera.getViewMatrix()[0][2];
        posMatrix[2][1] = camera.getViewMatrix()[1][2];
        posMatrix[2][2] = camera.getViewMatrix()[2][2];
        glm::mat4 rotMatrix = glm::rotate(i.getRotation(), glm::vec3(0, 0, 1));
        glm::mat4 scaleMatrix = glm::scale(glm::vec3(i.getScale(), i.getScale(), i.getScale()));
        glm::mat4 modelMatrix = posMatrix * rotMatrix * scaleMatrix;

        glm::mat4 matrix = camera.getViewMatrix() * modelMatrix;

        matrices.push_back(matrix);
        colors.push_back(i.getColor());

    }

    m_shader.bind();
    glDisable(GL_CULL_FACE);
    m_quad.bind();

    m_shader.loadProjection(camera.getProjectionMatrix());

    m_quad.pushMatrices(matrices);
    m_quad.pushColors(colors);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, matrices.size());

    m_quad.unbind();
    glEnable(GL_CULL_FACE);
    m_shader.unbind();

}

void ParticleRenderer::placeParticlesAroundBlock(int x, int y, int z, const vec3& color){
     for(unsigned int j = 0; j < Constants::getNumParticles(); j++){
          particles.emplace_back(colors[blockID], glm::vec3(x, y, z) + glm::vec3((rand()%11) / 10.0f, (rand()%11)/10.0f, (rand()%11)/10.0f), glm::vec3((rand()%10) - 5, 10, (rand()%10) - 5) * 0.20f, 1.25f, 0.0f, 0.125f);
     }
}


void ParticleRenderer::destroy(){

    particles.clear();
    m_quad.destroy();
    m_shader.destroy();

}
