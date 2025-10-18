/* This header file contains all global variabls
 * used throughout multiple files */
#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <SDL3/SDL.h>

enum {
	PLAYER_UBUF_IDX,
	VIEW_UBUF_IDX,
};

extern struct {
	SDL_Window *window;
	SDL_GLContext context;
	unsigned int sprite_program;
	unsigned int array;
	unsigned int uniform_buffer[4];
} gl;

extern struct {
	int pos_x, pos_y;
	int vel_x, vel_y;
} player
#ifdef _GLOBAL_C
= { 0, 0, 0, 0 }
#endif
;

extern struct {
	int centre_x, centre_y;
	int width, height;
} view
#ifdef _GLOBAL_C
= { 0, 0, 0, 0 }
#endif
;

#endif
