#include "QuadShader.hpp"

void QuadShader::init(){
    loadShader("res/shaders/vignette_vertex_shader.glsl", "res/shaders/vignette_fragment_shader.glsl");
}
