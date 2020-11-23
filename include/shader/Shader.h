#pragma once
#include"glad/glad.h"
#include"glm/glm.hpp"
#include"glm/gtc/type_ptr.hpp"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

class  Shader
{
public:

	GLuint id;	// ��ɫ��id

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {


		// 1. ��ȡ�ļ�
		std::string vertex_code;
		std::string fragment_code;

		std::ifstream vertex_shader_file;
		std::ifstream fragment_shader_file;

		vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			// ���ļ�
			vertex_shader_file.open(vertexPath);
			fragment_shader_file.open(fragmentPath);

			// string ��
			std::stringstream vertex_shader_stream, fragment_shader_stream;

			// ���ļ����� << ��stringstream����
			vertex_shader_stream << vertex_shader_file.rdbuf();
			fragment_shader_stream << fragment_shader_file.rdbuf();

			vertex_code = vertex_shader_stream.str();
			fragment_code = fragment_shader_stream.str();

			std::cout << vertex_code << std::endl;
			std::cout << fragment_code << std::endl;

			vertex_shader_file.close();
			fragment_shader_file.close();

		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ." << std::endl;
			exit(-1);
		}


		const char* vertex_code_char = vertex_code.c_str();
		const char* fragment_code_char = fragment_code.c_str();

		// 2. ������ɫ��
		GLuint vertex_shader_id;
		GLuint fragment_shader_id;

		vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader_id, 1, &vertex_code_char, NULL);
		glCompileShader(vertex_shader_id);

		// ���compile��Ϣ
		checkCompileError(vertex_shader_id, "vertex_shader");

		fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader_id, 1, &fragment_code_char, NULL);
		glCompileShader(fragment_shader_id);

		// ���compile��Ϣ
		checkCompileError(fragment_shader_id, "fragment_shader");

		// ����shader program����ɫ����
		this->id = glCreateProgram();
		glAttachShader(this->id, vertex_shader_id);
		glAttachShader(this->id, fragment_shader_id);

		glLinkProgram(this->id);
		
		// ���shader_program ��Ϣ
		checkCompileError(this->id, "shader_program");

		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);
	};

	~Shader() {
		glDeleteProgram(this->id);

	};
	//
	void use();
	void setBool(const std::string &name, bool value);
	void setInt(const std::string &name, int value);
	void setFloat(const std::string &name, float value);
	
	void setVec3(const std::string &name, const glm::vec3 &value);
	
	void setVec4(const std::string &name, const glm::vec4 &value);

	void setMat4(const std::string &name, const glm::mat4 &value);


private:
	void checkCompileError(GLuint shader, std::string type);

};