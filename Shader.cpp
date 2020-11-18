#include "Shader.hpp"
#include "Utils.hpp"

void Shader::loadShader(const char* vs, const char* fs){

	m_vertexID = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vsCode = Utils::loadShader(vs);
	std::string fsCode = Utils::loadShader(fs);

	const char* vs_pointer = vsCode.c_str();
	const char* fs_pointer = fsCode.c_str();

	glShaderSource(m_vertexID, 1, &vs_pointer, 0);
	glShaderSource(m_fragmentID, 1, &fs_pointer, 0);

	GLint vsCompileStatus;
	GLint fsCompileStatus;

	glCompileShader(m_vertexID);
	glGetShaderiv(m_vertexID, GL_COMPILE_STATUS, &vsCompileStatus);
	if(!vsCompileStatus){
		printf("Failed to compile vertex shader: %s\n", vs);
	}

	glCompileShader(m_fragmentID);
	glGetShaderiv(m_fragmentID, GL_COMPILE_STATUS, &fsCompileStatus);
	if(!fsCompileStatus){
		printf("Failed to compile fragment shader: %s\n", fs);
	}

	m_programID = glCreateProgram();
	glAttachShader(m_programID, m_vertexID);
	glAttachShader(m_programID, m_fragmentID);
	glLinkProgram(m_programID);
	glValidateProgram(m_programID);


}

void Shader::bind(){
	glUseProgram(m_programID);
}

void Shader::unbind(){
	glUseProgram(0);
}

void Shader::destroy(){
	glDetachShader(m_programID, m_vertexID);
	glDetachShader(m_programID, m_fragmentID);
	glDeleteShader(m_vertexID);
	glDeleteShader(m_fragmentID);
	glDeleteProgram(m_programID);
}