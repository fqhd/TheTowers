#include "VignetteShader.hpp"

void VignetteShader::init(){
    loadShader("res/shaders/vignette_vertex_shader.glsl", "res/shaders/vignette_fragment_shader.glsl");
}
