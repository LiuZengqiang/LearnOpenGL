#version 330 core
out vec4 frag_color;

in vec2 tex_coord;

uniform sampler2D our_tex_1;
uniform sampler2D our_tex_2;

void main(){
	
	frag_color = mix(texture(our_tex_1, tex_coord), texture(our_tex_2, tex_coord), 0.2);

}