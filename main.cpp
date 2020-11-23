#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader/Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

// 0.1 ʹ������vao vbo��ʾ�������������һ������
// 0.2 ��shader��ʹ��uniform��������ʱ��ı���ɫ
// 0.3 ��shader��ʹ�ö��location�������������ж�ȡ���position��color����
// 0.4 ʹ��Shader Class����������
// 0.5 ʹ�ü���A��D������uniform��������������λ�ñ仯
// 0.6 ʹ��������ʾһ������(��Ϊ�Ǿ��Σ�������Ҫʹ��EBO)
// 0.7 ʹ����������ļ�.jpg��.png�ļ�
// 0.8 ʹ��glm::mat4 ���о���任
// �ص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// ���ڴ�С
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
float coordinate_x;
//// vertex shader code
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"layout (location = 1) in vec3 aCol;\n"
//"out vec3 our_color;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"	our_color = aCol;\n"
//"}\0";
//
//// fragment shader code
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 our_color;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(our_color, 1.0f);\n"
//"}\n\0";

int main()
{

	// glfw ��ʼ��
	glfwInit();
	// �汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ����GLFW_OPENGL_PROFILE Ϊ����ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// ���ɴ��� window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// ����������Ϊ�½���window
	glfwMakeContextCurrent(window);
	// ����window��С�ı�ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ʹ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ʹ��Shader��������������ɫ��
	Shader shader_program("E:\\VisualStudioProject\\LearnOpenGL\\src\\shaders\\vertexShader.vs", "E:\\VisualStudioProject\\LearnOpenGL\\src\\shaders\\fragmentShader.fs");

	//// ����һ��vertex��ɫ��id��vertexShader
	//// ������һ����ɫ������ֵ��id:vertexShader
	//int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//// ����vertex��ɫ������
	//// ����: ��ɫ����Դ�����ַ���������Դ�����ַ�����null
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//// ����vertex��ɫ��
	//glCompileShader(vertexShader);

	//// ���ڼ���Ƿ�ɹ�
	//int success;
	//char infoLog[512];

	//// get shader information value
	//// ��������ɫ��������״̬��Ŀ�����
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	// get ��ϸ����ɫ����Ϣ
	//	// ��������ɫ����Ŀ�������С�����ص��ַ����ȡ�Ŀ�����
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//// fragment shader
	//int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//// ��ɫ������shader program
	//int shaderProgram = glCreateProgram();
	//// ����vertex shader��fragment shader
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//// ������ɫ������
	//glLinkProgram(shaderProgram);

	//// ���shader program������Ϣ
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	//}

	//// �������Ӻ�֮�����ɾ��֮ǰ��vertex shader��fragment shader
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	// ��λ������
	//float vertices[] = {
	//	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	//	0.5f, -0.5f, 0.0f,  // ���½�
	//	-0.5f, -0.5f, 0.0f // ���½�
	//	//-0.5f, 0.5f, 0.0f   // ���Ͻ�
	//};

	// ����������������������
	GLuint texture_id[2];
	glGenTextures(2, texture_id);

	// ����GL_TEXTURE0
	glActiveTexture(GL_TEXTURE0);
	// ���������
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);

	// ���û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// ��������ͼƬ
	// ��ȡ��߶Ⱥ���ɫͨ�����������ڴ���ͨ������?
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("E:\\VisualStudioProject\\LearnOpenGL\\src\\img\\wall.jpg", &width, &height, &nrChannels, 0);

	if (data) {
		// ����ͼƬ.jpg��������
		// ����:�������͡��༶��������������洢��ʽ����ȡ��߶ȡ�Ĭ��0(��ʷ��������)��Դͼ��ʽ��Դͼ��������(char(byte))��ͼ����
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		// ���ɶ༶��������(���ֻ��һ��Ļ������Ƿ���Բ���?)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR:Failed to load texture." << std::endl;
		exit(1);
		
	}
	// �ͷ�ͼƬԴ����
	stbi_image_free(data);


	glActiveTexture(GL_TEXTURE1);
	// ��ʼ���ڶ����������
	// ��
	glBindTexture(GL_TEXTURE_2D, texture_id[1]);

	// ���û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	
	// ����ͼƬ
	data = stbi_load("E:\\VisualStudioProject\\LearnOpenGL\\src\\img\\awesomeface.png", &width, &height, &nrChannels, 0);

	if (data) {
		// ����ͼƬ.jpg��������
		// ����:�������͡��༶��������������洢��ʽ����ȡ��߶ȡ�Ĭ��0(��ʷ��������)��Դͼ��ʽ��Դͼ��������(char(byte))��ͼ����
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		// ���ɶ༶��������(���ֻ��һ��Ļ������Ƿ���Բ���?)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR:Failed to load texture." << std::endl;
		exit(1);

	}
	// �ͷ�ͼƬԴ����
	stbi_image_free(data);

	// ��λ�����ݡ�����ɫ���ݺ͵��������������
	float vertices_p_c_t[] = {
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 1.0f,   2.0f, 2.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left 
	};

	/*float vertixes_2[] = {
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};*/

	// ���Ƶ���������
	unsigned int indices[] = { // ע��������0��ʼ! 
		0, 1, 2, // first triangle
		2, 3, 0  // second triangle
	};

	// ����vbo��vertex buffer object��id �� vao��vertex array object��id
	//unsigned int VBO, VAO, EBO;
	unsigned int VAO, VBO;
	GLuint EBO;
	// ����vbo��vao���󣬲���vbo��vao�����id��
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// ��vao
	// �ڽ��vao֮ǰ ���ж�vbo�Ĳ������ڸ�vao��
	glBindVertexArray(VAO);

	// ��vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// �������ݵ�vbo��
	// ����:GL_ARRAY_BUFFER�����ݴ�С�������׵�ַ��GL_STATIC_DRAW
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_p_c_t), vertices_p_c_t, GL_STATIC_DRAW);
	// �������ݵ�ebo��
	// ����:GL_ELEMENT_ARRAY_BUFFER�����ݴ�С�������׵�ַ��GL_STATIC_DRAW
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ����openGL���ݵĽ�����ʽ��ÿһ��vertex��ν�����
	// ����openGL�Ķ�����ɫ����location==0�ı���������δ�buffer�ж�ȡ
	// ����:location���������Դ�С�����͡��Ƿ��׼������������ʼƫ��
	// location = 0, position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// location = 1, color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// location = 2, texture coordinate
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);


	// ���vao
	glBindVertexArray(0);
	// ���vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//// ��vao[1]
	//glBindVertexArray(VAO[1]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertixes_2), vertixes_2, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);


	// ���ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// �߿�ģʽ
	// ��������:ǰ��ͺ��涼���ƣ��߿�
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ����shader_program��������uniform����
	shader_program.use();
	
	// ����shader��sampler��Ӧ��GL_TEXTUREx
	shader_program.setInt("our_tex_1", 0);
	shader_program.setInt("our_tex_2", 1);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ��GL_TEXTURE_2DΪtexture_id
		// (֮ǰ�Ѿ��󶨹�������û�н�󣬿��Բ����ٴΰ�)
		//glBindTexture(GL_TEXTURE_2D, texture_id);

		// ��ʼ����
		// ���뼤��shader program���ܽ�����������
		//glUseProgram(shaderProgram);

		//// ����texture
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture_id[0]);

		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture_id[1]);

		shader_program.use();
		// �任
		// �任����
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
		
		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		shader_program.setMat4("transform", trans);

		/*float now_time = glfwGetTime();*/

		/*	float green_color = sin(now_time) / 2.0f + 0.5f;
			std::cout << green_color << std::endl;
			int our_color_location = glGetUniformLocation(shaderProgram, "our_color");

			glUniform4f(our_color_location, 0.0f, green_color, 0.0f, 1.0f);*/


		shader_program.setFloat("coord_x", coordinate_x);

		//// ��vao
		//glBindVertexArray(VAO[0]);
		//// ��ʹ��ebo����
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//// ���vao
		//glBindVertexArray(0);

		glBindVertexArray(VAO);
		// ʹ��ebo����
		// ����: GL_TRIANGLES��(����)�������������������ͣ�ƫ��
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//glDeleteProgram(shaderProgram);
	//delete &shader_program;

	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		coordinate_x += 0.001f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		coordinate_x -= 0.001f;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}