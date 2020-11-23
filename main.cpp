#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader/Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

// 0.1 使用两个vao vbo显示两个三角形组成一个矩形
// 0.2 在shader中使用uniform变量，随时间改变颜色
// 0.3 在shader中使用多个location变量，从数据中读取点的position和color数据
// 0.4 使用Shader Class绘制三角形
// 0.5 使用键盘A、D按键和uniform变量控制三角形位置变化
// 0.6 使用纹理显示一个矩形(因为是矩形，所以需要使用EBO)
// 0.7 使用零个纹理文件.jpg和.png文件
// 0.8 使用glm::mat4 进行矩阵变换
// 回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// 窗口大小
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

	// glfw 初始化
	glfwInit();
	// 版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 设置GLFW_OPENGL_PROFILE 为核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// 生成窗口 window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// 设置上下文为新建的window
	glfwMakeContextCurrent(window);
	// 设置window大小改变回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 使用glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 使用Shader类声明并定义着色器
	Shader shader_program("E:\\VisualStudioProject\\LearnOpenGL\\src\\shaders\\vertexShader.vs", "E:\\VisualStudioProject\\LearnOpenGL\\src\\shaders\\fragmentShader.fs");

	//// 声明一个vertex着色器id，vertexShader
	//// 并产生一个着色器，赋值给id:vertexShader
	//int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//// 设置vertex着色器代码
	//// 参数: 着色器、源代码字符串个数、源代码字符串、null
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//// 编译vertex着色器
	//glCompileShader(vertexShader);

	//// 用于检查是否成功
	//int success;
	//char infoLog[512];

	//// get shader information value
	//// 参数：着色器、编译状态、目标变量
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	// get 详细的着色器信息
	//	// 参数：着色器、目标变量大小、返回的字符长度、目标变量
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

	//// 着色器程序shader program
	//int shaderProgram = glCreateProgram();
	//// 附加vertex shader和fragment shader
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//// 链接着色器程序
	//glLinkProgram(shaderProgram);

	//// 检查shader program链接信息
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	//}

	//// 程序连接好之后可以删除之前的vertex shader和fragment shader
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	// 点位置数据
	//float vertices[] = {
	//	0.5f, 0.5f, 0.0f,   // 右上角
	//	0.5f, -0.5f, 0.0f,  // 右下角
	//	-0.5f, -0.5f, 0.0f // 左下角
	//	//-0.5f, 0.5f, 0.0f   // 左上角
	//};

	// 生成纹理对象，两个纹理对象
	GLuint texture_id[2];
	glGenTextures(2, texture_id);

	// 激活GL_TEXTURE0
	glActiveTexture(GL_TEXTURE0);
	// 绑定纹理对象
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);

	// 设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 加载纹理图片
	// 宽度、高度和颜色通道个数，和期待的通道个数?
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("E:\\VisualStudioProject\\LearnOpenGL\\src\\img\\wall.jpg", &width, &height, &nrChannels, 0);

	if (data) {
		// 根据图片.jpg生成纹理
		// 参数:纹理类型、多级纹理渐进级别、纹理存储方式、宽度、高度、默认0(历史遗留问题)、源图格式、源图数据类型(char(byte))、图数据
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		// 生成多级渐进纹理(如果只用一层的话这里是否可以不用?)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR:Failed to load texture." << std::endl;
		exit(1);
		
	}
	// 释放图片源数据
	stbi_image_free(data);


	glActiveTexture(GL_TEXTURE1);
	// 初始化第二个纹理对象
	// 绑定
	glBindTexture(GL_TEXTURE_2D, texture_id[1]);

	// 设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	
	// 加载图片
	data = stbi_load("E:\\VisualStudioProject\\LearnOpenGL\\src\\img\\awesomeface.png", &width, &height, &nrChannels, 0);

	if (data) {
		// 根据图片.jpg生成纹理
		// 参数:纹理类型、多级纹理渐进级别、纹理存储方式、宽度、高度、默认0(历史遗留问题)、源图格式、源图数据类型(char(byte))、图数据
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		// 生成多级渐进纹理(如果只用一层的话这里是否可以不用?)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR:Failed to load texture." << std::endl;
		exit(1);

	}
	// 释放图片源数据
	stbi_image_free(data);

	// 点位置数据、点颜色数据和点的纹理坐标数据
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

	// 绘制的索引数据
	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 2, // first triangle
		2, 3, 0  // second triangle
	};

	// 声明vbo，vertex buffer object，id 和 vao，vertex array object，id
	//unsigned int VBO, VAO, EBO;
	unsigned int VAO, VBO;
	GLuint EBO;
	// 产生vbo和vao对象，并与vbo，vao对象的id绑定
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 绑定vao
	// 在解绑vao之前 所有对vbo的操作都在该vao中
	glBindVertexArray(VAO);

	// 绑定vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// 复制数据到vbo中
	// 参数:GL_ARRAY_BUFFER、数据大小、数据首地址、GL_STATIC_DRAW
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_p_c_t), vertices_p_c_t, GL_STATIC_DRAW);
	// 复制数据到ebo中
	// 参数:GL_ELEMENT_ARRAY_BUFFER、数据大小、数据首地址、GL_STATIC_DRAW
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 告诉openGL数据的解析方式（每一个vertex如何解析）
	// 告诉openGL的顶点着色器，location==0的变量数据如何从buffer中读取
	// 参数:location、顶点属性大小、类型、是否标准化、步长、起始偏移
	// location = 0, position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// location = 1, color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// location = 2, texture coordinate
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);


	// 解绑vao
	glBindVertexArray(0);
	// 解绑vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//// 绑定vao[1]
	//glBindVertexArray(VAO[1]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertixes_2), vertixes_2, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);


	// 解绑ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// 线框模式
	// 参数含义:前面和后面都绘制，线框
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 激活shader_program用来设置uniform变量
	shader_program.use();
	
	// 设置shader中sampler对应的GL_TEXTUREx
	shader_program.setInt("our_tex_1", 0);
	shader_program.setInt("our_tex_2", 1);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 绑定GL_TEXTURE_2D为texture_id
		// (之前已经绑定过，假如没有解绑，可以不用再次绑定)
		//glBindTexture(GL_TEXTURE_2D, texture_id);

		// 开始绘制
		// 必须激活shader program才能进行其他操作
		//glUseProgram(shaderProgram);

		//// 激活texture
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture_id[0]);

		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture_id[1]);

		shader_program.use();
		// 变换
		// 变换矩阵
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

		//// 绑定vao
		//glBindVertexArray(VAO[0]);
		//// 不使用ebo绘制
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//// 解绑vao
		//glBindVertexArray(0);

		glBindVertexArray(VAO);
		// 使用ebo绘制
		// 参数: GL_TRIANGLES，(索引)顶点数，索引数据类型，偏移
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