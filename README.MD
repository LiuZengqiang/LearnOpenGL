# Learn OpenGL core model.
一个vao中可以又多个vbo(最多16个)
例如:对于一个点，需要有position和color信息
我们可以生成两个vbo(即两个buffer)，一个buffer中存position数据，
另一个存color数据，这两个vbo可以在一个vao中
使用location区分数据，使用glEnableVertexAtrribArray和
alVertexAtrribPoint(location,size,type,normalize,stride,deviation);
区分每个vbo代表的数据的含义和是否使用enable

什么是EBO?element buffer object，索引缓冲对象。
存储索引的缓冲
一个vao中只有一个ebo，所以与vbo不同的是，在解绑vao之前不能解绑ebo.

在不用ebo之前，绘制使用	glDrawArrays(GL_TRIANGLES, 0, 3);
在使用ebo之后，绘制使用 glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

顶点着色器(vertexShader)从数据中直接读取数据，因此需要使用location指定输入数据
线段着色器fragment shader需要输出一个vec4颜色输出变量
(在代码中我们使用gl_FragColor这个默认变量设置颜色，因此只声明了输出，
但是并没有真的输出)

着色器中的uniform变量：
uniform 是全局的，在各个着色器中都可以使用
在main函数中使用 int uniformLocation = glGetUniformLoaction(shaderProgram, "uniform name");
获取uniform 的location，再使用glUniform4f(uniformLocation,x,y,z,w);设置变量值。

文件数据读取过程：
相关变量
string data_str;	//最终的数据
string file_path;	//文件路径
ifstream file;		//文件
stringstream string_stream;	//string流

file.open(file_path);
string_stream << file.rdbuf();
file.close();
data_str = string_stream.str();

!!!一定要注意点的坐标position:x,y,z,w中的w分量要设为1.0，不然w==0时会被认定为点的的位置为无限远

texture(sampler,texture_coordinate)是GLSL内的内建函数

使用纹理的过程:
1. 生成纹理对象：
	GLuint tex_id;
	glGenTextures(1, &tex_id);
2. 绑定纹理对象
	glBindTexture(GL_TEXTURE_2D, tex_id);
3. 设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D,...,...);
4. 加载纹理图片
	unsigned char* data = stbi_load(...);
	jpg与png图片加载有一点不同，jpg是RGB，而png是RGBA，多了一个alpha(透明度)
5. 生成纹理、生成多级渐进纹理
	glTexImage2D(...)
	glGenerateMipmap(GL_TEXTURE_2D);
6. 释放图片数据
	stbi_image_free(data);
同时在fragment shader中使用
	frag_color = texture(sampler2D, tex_coordinate);
设置不同坐标处的纹理样式
同时使用多个纹理时(最多16个)：
	在shader_program中声明多个sampler2D，对每个texture执行：1. 2. 3. 4. 5. 6.
	在绘制之前:设定每个sampler2D的变量值(0-15)，
	在绘制时:先激活对应的GL_TEXTURE0，再绑定对应的texture_0。(GL_TEXTURE0默认激活状态)
	
	再说一点，opengl是一个状态机，初始时默认激活GL_TEXTURE0,
	由于"2."中需要glBindTexture(GL_TEXTURE_2D,...);因此如果不手动的激活其他GL_TEXTUREx，那么最后GL_TEXTURE0中代表的是最后一个texture，
	在绘制时需要:
		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture_id0);
		glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, texture_id1);
		...
	虽然可以在生成texture时手动改变对应glActiveTexture(x)，但是建议按照教程代码，在生成所有texture之后，在绘制之前使用
		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture_id0);
		glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, texture_id1);
	再一起设置GL_TEXTUREx具体的texture(就让开始是只有最后一个texture与GL_TEXTURE0对应吧，主不在乎)。

变换时的矩阵依旧按照从后往前运算。
	