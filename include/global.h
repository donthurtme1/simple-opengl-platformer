/* This header file contains all global variabls
 * used throughout multiple files */
#ifndef _GLOBAL_H
#define _GLOBAL_H

#define LEN(array) (sizeof(array) / sizeof(array[0]))

#include <SDL3/SDL.h>
#include "types.h"

enum {
	PLAYER_UBUF_IDX,
	VIEW_UBUF_IDX,
	LEVEL_UBUF_IDX,
};

extern struct {
	SDL_Window *window;
	SDL_GLContext context;
	/* Shader programs */
	unsigned int sprite_program;
	unsigned int tile_program;
	/* Square vertex array and buffer */
	unsigned int v_array;
	unsigned int v_buffer; /* NOTE: currently this is unused */
	/* Uniform buffers */
	unsigned int uniform_buffer[4];
	/* GL Textures */
	unsigned int tile_atlas;
	unsigned int sprite_atlas;
} gl;

extern struct {
	/* Physics */
	struct Vec2 pos;
	struct Vec2 vel;
	struct Vec2 accel;
	/* Sprite */
	int anim_id; /* 0 is idle, 1 is walking */
	int anim_frame; /* Number from 0 - 3, only 4 frames */
	bool face_left;

	/* Input */
	enum PlayerInput {
		INKEY_UP	= 1 << 0,
		INKEY_LEFT	= 1 << 1,
		INKEY_DOWN	= 1 << 2,
		INKEY_RIGHT	= 1 << 3,
		INKEY_JUMP	= 1 << 4,
	} key_bitmask;
	int x_input, y_input;
} player;

extern struct {
	int centre_x, centre_y;
	int width, height;
} view;

extern struct terrain_rect {
	struct Rect area;
	enum TileID {
		TILE_NONE		  = -1,
		TILE_GROUND		  = 0,
		TILE_BRICKS		  = 1,
		TILE_SHROOM_HEAD  = 2,
		TILE_SHROOM_STALK = 3,
	} tileid;
} __attribute__((aligned(8))) level_data[512];

#endif
