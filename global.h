/* This header file contains all global variabls
 * used throughout multiple files */
#ifndef _GLOBAL_H
#define _GLOBAL_H

#define LEN(array) (sizeof(array) / sizeof(array[0]))

#include <SDL3/SDL.h>

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
	int pos_x, pos_y;
	int vel_x, vel_y;
	int accel_x, accel_y;
	int anim;
	int anim_frame; /* Number from 0 - 3, only 4 frames */

	enum PlayerInput {
		INKEY_UP	= 1 << 0,
		INKEY_LEFT	= 1 << 1,
		INKEY_DOWN	= 1 << 2,
		INKEY_RIGHT	= 1 << 3,
	} key_bitmask;
	int x_input, y_input;
} player;

extern struct {
	int centre_x, centre_y;
	int width, height;
} view;

#endif
