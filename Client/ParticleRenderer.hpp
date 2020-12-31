#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H
#include "ParticleQuad.hpp"
#include "ParticleShader.hpp"
#include "Particle.hpp"
#include "Camera.hpp"
#include <vector>

class ParticleRenderer {
public:

    void init();
    void update(float deltaTime);
    void render(Camera& camera);
    void destroy();

    void placeParticlesAroundBlock(int x, int y, int z, const vec3& color);

    std::vector<Particle> particles;


private:

    ParticleQuad m_quad;
    ParticleShader m_shader;

};

#endif
