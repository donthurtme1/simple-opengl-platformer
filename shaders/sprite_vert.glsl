/* Sprite vertex shader */
#version 460

vec2 varray[4] = {
	vec2(-1, -1),
	vec2( 1, -1),
	vec2(-1,  1),
	vec2( 1,  1),
};

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
			(varray[gl_VertexID].x / 100) + (float(pos_x) / 1000),
			(varray[gl_VertexID].y / 100) + (float(pos_y) / 1000),
			0, 1);
}
