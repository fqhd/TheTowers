#ifndef QUAD_SHADER_H
#define QUAD_SHADER_H

#include "Shader.hpp"
#include <glm/glm.hpp>


class BlockOutlineShader : public Shader {
public:

     //Public utility functions
     void init();

     //Uniform Loading Functions
     void loadProjectionMatrix(const glm::mat4& matrix);
     void loadViewMatrix(const glm::mat4& matrix);
		 void loadBlockPosition(const glm::vec3& position);

private:

     //Private Functions
     void getUniformLocations();


     //OpenGL Variables
     GLint m_projectionMatrixLocation = 0;
     GLint m_viewMatrixLocation = 0;
     GLint m_blockPositionLocation = 0;

};

#endif
