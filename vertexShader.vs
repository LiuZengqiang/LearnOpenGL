#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
out vec3 our_color;
void main(){
	gl_position = vec4(aPos.x, aPos.y, aPos.z, 0.0f);
	our_color = aCol;
}