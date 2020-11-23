#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTex;

uniform float coord_x;

out vec3 our_color;
out vec2 tex_coord;

uniform mat4 transform;

void main(){

	gl_Position = transform * vec4(aPos.x+coord_x, aPos.y, aPos.z, 1.0f);
	our_color = aCol;
	tex_coord = aTex;
}
