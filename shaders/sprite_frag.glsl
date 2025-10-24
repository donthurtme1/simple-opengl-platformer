/* Sprite fragment shader */
#version 460

layout(location=0) in vec2 in_texcoord;
layout(location=1) in vec2 in_texoffs;

out vec4 out_colour;

uniform sampler2D in_spriteatlas;

void main() {
	vec2 coord = in_texoffs + (vec2(0.25f, 0.25f) * fract(in_texcoord));
	out_colour = texture(in_spriteatlas, coord);
}
