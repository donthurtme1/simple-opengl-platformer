/* Sprite vertex shader */
#version 460
#extension GL_EXT_gpu_shader4 : enable

vec2 anim_frames[3] = {
	vec2(0, 0),		// stand
	vec2(0.25f, 0),	// step one
	vec2(0.5f, 0),	// step two
};

layout(location=0) in vec2 in_pos;

layout(location=0) out vec2 out_texcoord;
layout(location=1) out vec2 out_texoffs;

/* Uniform bindings */
layout(binding=0) uniform Player {
	int pos_x, pos_y;
	int vel_x, vel_y;
	int accel_x, accel_y;
	int anim, anim_frame; /* Number from 0 - 3, only 4 frames */
};

layout(binding=1) uniform View {
	int centre_x, centre_y;
	int width, height;
};

void main() {
	vec2 tex_coords[4] = {
		vec2(0, 1),
		vec2(1, 1),
		vec2(0, 0),
		vec2(1, 0),
	};
	out_texcoord = tex_coords[gl_VertexID];
	if (anim == 1) {
		out_texoffs = vec2(0.25f *
				((anim_frame & 1) + ((anim_frame & 1) * (anim_frame / 2))), 0);
	} else {
		out_texoffs = vec2(0, 0);
	}

	gl_Position = vec4(
			(in_pos.x / 8) + (float(pos_x) / (8 * 16 * 16)),
			(in_pos.y / 8) + (float(pos_y) / (8 * 16 * 16)),
			-0.5f, 1);
	gl_Position.x *= (float(height) / width);
}
