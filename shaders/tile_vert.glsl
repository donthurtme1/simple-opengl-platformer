/* Tile vertex shader */
#version 460

vec2 tex_offsets[4] = {
	vec2(0, 0),		// grass texture
	vec2(0.25f, 0),	// brick texture
	vec2(0.5f, 0),	// mushroom texture
	vec2(0.75f, 0),	// stalk texture
};

layout(location=0) out vec2 out_texcoord;
layout(location=1) out vec2 out_texoffs;

/* Uniform buffers */
layout(binding=1) uniform View {
	int centre_x, centre_y;
	int width, height;
};

struct TerrainRect {
	ivec2 pos;
	ivec2 rect;
	int type;
};
layout(binding=2) uniform Terrain {
	TerrainRect level[512];
};

void main() {
	vec2 varray[4] = {
		vec2(0, 0),
		vec2(level[gl_InstanceID].rect.x, 0),
		vec2(0, level[gl_InstanceID].rect.y),
		vec2(level[gl_InstanceID].rect.x, level[gl_InstanceID].rect.y),
	};

	vec2 tex_coords[4] = {
		vec2(0, level[gl_InstanceID].rect.y),
		vec2(level[gl_InstanceID].rect.x, level[gl_InstanceID].rect.y),
		vec2(0, 0),
		vec2(level[gl_InstanceID].rect.x, 0),
	};
	out_texcoord = tex_coords[gl_VertexID];
	out_texoffs = tex_offsets[level[gl_InstanceID].type];

	gl_Position = vec4(
			(varray[gl_VertexID].x / 8) + 
			(float(level[gl_InstanceID].pos.x) / 8),
			(varray[gl_VertexID].y / 8) + 
			(float(level[gl_InstanceID].pos.y) / 8),
			0, 1);
	gl_Position.x *= (float(height) / width);
}
