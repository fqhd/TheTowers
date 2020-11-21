#pragma once
#include "ParticleQuad.hpp"
#include "ParticleShader.hpp"
#include "Particle.hpp"
#include "Camera.hpp"
#include <vector>

class ParticleRenderer {
public:

    void init();
    void update(float deltaTime);
    void render(const Camera& camera);
    void destroy();

    std::vector<Particle> particles;


private:

    ParticleQuad m_quad;
    ParticleShader m_shader;

};
