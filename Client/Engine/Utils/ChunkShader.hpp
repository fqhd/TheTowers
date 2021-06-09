#ifndef CHUNK_SHADER_H
#define CHUNK_SHADER_H
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include "Utils.hpp"
#include "Shader.hpp"


class ChunkShader : public Shader {
public:

	void init();
	void loadProjectionMatrix(const glm::mat4& matrix);
	void loadViewMatrix(const glm::mat4& matrix);
	void loadGradient(float gradient);
	void loadDensity(float density);


private:

	void getUniformLocations();

	GLint m_viewMatrixLocation = 0;
	GLint m_projectionMatrixLocation = 0;
	GLint m_densityLocation = 0;
	GLint m_gradientLocation = 0;

};

#endif
