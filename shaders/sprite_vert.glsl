/* Sprite vertex shader */
#version 460

layout(location=0) in vec2 in_pos;

/* Uniform bindings */
layout(binding=0) uniform Player {
	int pos_x, pos_y;
};

layout(binding=1) uniform View {
	int centre_x, centre_y;
	int width, height;
};

void main() {
	gl_Position = vec4(
			(in_pos.x / 12) + (float(pos_x) / (12 * 16 * 16)),
			(in_pos.y / 12) + (float(pos_y) / (12 * 16 * 16)),
			0, 1);
}
