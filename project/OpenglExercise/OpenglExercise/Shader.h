#pragma once
#include "string"
#include "glm/glm.hpp"
class Shader
{
public:
	//shader program id
	unsigned int ID;
	//constructor generates the shader on the fly
	Shader(const char* vertexPath, const char* fragmentPath);
	//activate the shader
	void use();

	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	

private:
	// utility function for checking shader compilation/linking errors.
	void checkCompileErrors(unsigned int shader, std::string type);
};

