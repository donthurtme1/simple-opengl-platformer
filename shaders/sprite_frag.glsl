/* Sprite fragment shader */
#version 460

layout(location=0) in vec4 in_colour;

out vec4 out_colour;

void main() {
	out_colour = vec4(0.8f, 0, 0, 1);
}
