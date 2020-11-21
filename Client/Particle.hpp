#pragma once
#include <glm/glm.hpp>
#include "Vertex.hpp"

class Particle {
public:

    Particle(const vec3& color, const glm::vec3& position, const glm::vec3& velocity, float gFactor, float lifelength, float rotation, float scale);

    bool update(float deltaTime);

    const glm::vec3& getPosition() const;
    const vec3& getColor();
    float getRotation() const;
    float getScale() const;
    float getLifeLength() const;
    float getElapsedTime() const;



private:

        vec3 m_color;
        glm::vec3 m_position;
        glm::vec3 m_velocity;
        float m_gFactor = 0.0f;
        float m_lifeLength = 0.0f;
        float m_rotation = 0.0f;
        float m_scale = 0.0f;
        float m_elapsedTime = 0.0f;

};
