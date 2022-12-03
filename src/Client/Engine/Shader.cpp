#include "Shader.hpp"
#include "Utils.hpp"
#include "FilePathManager.hpp"

void Shader::load(const std::string& name){
	std::string vs = FilePathManager::getRootFolderDirectory() + "res/shaders/" + name + "/vertex_shader.glsl";
	std::string fs = FilePathManager::getRootFolderDirectory() + "res/shaders/" + name + "/fragment_shader.glsl";

	m_vertexID = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vsCode = Utils::readFileToString(vs);
	std::string fsCode = Utils::readFileToString(fs);

	const char* vs_pointer = vsCode.c_str();
	const char* fs_pointer = fsCode.c_str();

	glShaderSource(m_vertexID, 1, &vs_pointer, 0);
	glShaderSource(m_fragmentID, 1, &fs_pointer, 0);

	GLint vsCompileStatus;
	GLint fsCompileStatus;

	glCompileShader(m_vertexID);
	glGetShaderiv(m_vertexID, GL_COMPILE_STATUS, &vsCompileStatus);
	if(!vsCompileStatus){
		std::cout << "Shader: Failed to compile vertex shader: " << vs << std::endl;
	}

	glCompileShader(m_fragmentID);
	glGetShaderiv(m_fragmentID, GL_COMPILE_STATUS, &fsCompileStatus);
	if(!fsCompileStatus){
		std::cout << "Shader: Failed to compile fragment shader: " << fs << std::endl;
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

GLint Shader::getUniformLocation(const std::string& name){
	auto it = m_uniformLocations.find(name);
	if(it == m_uniformLocations.end()){
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		m_uniformLocations[name] = location;
		return location;
	}
	return it->second;
}

void Shader::loadUniform(const std::string& name, const glm::vec3& vec){
	glUniform3fv(getUniformLocation(name), 1, &vec.x);
}

void Shader::loadUniform(const std::string& name, const glm::mat4& matrix){
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::loadUniform(const std::string& name, float f){
	glUniform1f(getUniformLocation(name), f);
}

void Shader::loadUniform(const std::string& name, int i){
	glUniform1i(getUniformLocation(name), i);
}

void Shader::loadUniform(const std::string& name, bool b){
	int value = (int)b;
	glUniform1i(getUniformLocation(name), value);
}