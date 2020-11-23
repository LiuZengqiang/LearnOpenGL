#include"Shader.h"


void Shader::use()
{
	glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value)
{
	GLint location = glGetUniformLocation(this->id, name.c_str());

	glUniform1i(location, (int)value);
}

void Shader::setInt(const std::string& name, int value)
{
	GLint location = glGetUniformLocation(this->id, name.c_str());
	glUniform1i(location, value);
}

void Shader::setFloat(const std::string& name, float value)
{
	GLint location = glGetUniformLocation(this->id, name.c_str());
	glUniform1f(location, value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	GLint location = glGetUniformLocation(this->id, name.c_str());
	glUniform3fv(location, 1, &value[0]);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value)
{
	GLint location = glGetUniformLocation(this->id, name.c_str());
	glUniform4fv(location, 1, &value[0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value)
{
	GLuint location = glGetUniformLocation(this->id, name.c_str());
	
	// 参数:
	// location、矩阵的个数、是否转置矩阵、矩阵数据(需要先使用value_ptr()变换数据)
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::checkCompileError(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[512];
	if (type == "shader_program") {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINK_ERROR::" << infoLog << "." << std::endl;
			exit(-1);
		}
	}
	else {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR:SHADER_COMPILATION_ERROR::" << type << infoLog << "." << std::endl;
			exit(-1);
		}
	}
}
