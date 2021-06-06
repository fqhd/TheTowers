#ifndef MODEL_SHADER_H
#define MODEL_SHADER_H

#include "Shader.hpp"
#include "Vertex.hpp"
#include <glm/glm.hpp>


class ModelShader : public Shader {
public:

  void init();
  void loadColor(const vec3& color);
	void loadLightDirection(const glm::vec3& lightDir);
  void loadProjectionMatrix(const glm::mat4& matrix);
	void loadViewMatrix(const glm::mat4& matrix);
  void loadModelMatrix(const glm::mat4& matrix);
  void loadGradient(float gradient);
  void loadDensity(float density);

private:

  //Functions
  void getUniformLocations();

  //Uniform Locations
  GLint m_colorLocation = 0;
  GLint m_viewMatrixLocation = 0;
  GLint m_projectionMatrixLocation = 0;
  GLint m_modelMatrixLocation = 0;
  GLint m_densityLocation = 0;
	GLint m_gradientLocation = 0;
	GLint m_lightDirectionLocation = 0;
};

#endif
