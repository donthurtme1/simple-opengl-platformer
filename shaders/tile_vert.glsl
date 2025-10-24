/* Tile vertex shader */
#version 460

vec3 colours[4] = {
	vec3(0, 0.8f, 0),		// grass
	vec3(0.4f, 0.2f, 0),	// brick
	vec3(0.7f, 0, 0),		// mushroom
	vec3(0.7f, 0.6f, 0.5f)	// stalk
};
vec2 tex_offsets[4] = {
	vec2(0, 0),		// grass texture
	vec2(0.25f, 0),	// brick texture
	vec2(0.5f, 0),	// mushroom texture
	vec2(0.75f, 0),	// stalk texture
};

layout(location=0) out vec3 out_colour;
layout(location=1) out vec2 out_texcoord;
layout(location=2) out vec2 out_texoffs;

/* Uniform buffers */
layout(binding=1) uniform View {
	int centre_x, centre_y;
	int width, height;
};

struct LevelNode {
	vec2 pos;
	ivec2 rect;
	int type;
};
layout(binding=2) uniform Terrain {
	LevelNode level[512];
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

	out_colour = colours[level[gl_InstanceID].type];
	gl_Position = vec4(
			(varray[gl_VertexID].x / 8) + 
			(level[gl_InstanceID].pos.x / 8),
			(varray[gl_VertexID].y / 8) + 
			(level[gl_InstanceID].pos.y / 8),
			0, 1);
	gl_Position.x *= (float(height) / width);
}
