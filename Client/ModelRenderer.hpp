#pragma once
#include <vector>
#include "Entity.hpp"
#include "ModelShader.hpp"
#include "Camera.hpp"
#include "Vertex.hpp"

class ModelRenderer {
public:

    void init();
    void render(Camera& camera, float range);
    void destroy();

    std::vector<Entity> entities;

private:

    ModelShader m_shader;

};
