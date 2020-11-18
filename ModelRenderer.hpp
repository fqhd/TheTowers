#pragma once
#include <vector>
#include "Model.hpp"
#include "ModelShader.hpp"
#include "Camera.hpp"

class ModelRenderer {
public:

    void init();
    void render(Camera& camera);
    void destroy();

    std::vector<Model> models;

private:

    ModelShader m_shader;

};