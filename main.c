#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <SDL3/SDL.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "global.h"

extern int init_all(void);
extern void move_player(int x, int y);
extern void update_player(void);
extern void player_input(enum PlayerInput key, bool key_down);

int main(void) {
	int res = init_all();
	if (res == -1)
		write(1, "slag\n", 5);

	/* Main loop */
	struct timespec monotime;
	clock_gettime(CLOCK_MONOTONIC, &monotime);
	while (1) {
		/* Events */
		SDL_Event event;
		while (SDL_PollEvent(&event) == 1) {
			if (event.type == SDL_EVENT_QUIT)
				return 0;
			else if (event.type == SDL_EVENT_KEY_DOWN) {
				switch (event.key.key) {
					case SDLK_A: player_input(INKEY_UP, 1);
								 break;
					case SDLK_S: player_input(INKEY_LEFT, 1);
								 break;
					case SDLK_D: player_input(INKEY_DOWN, 1);
								 break;
					case SDLK_F: player_input(INKEY_RIGHT, 1);
								 break;
				}
			}
			else if (event.type == SDL_EVENT_KEY_UP) {
				switch (event.key.key) {
					case SDLK_A: player_input(INKEY_UP, 0);
								 break;
					case SDLK_S: player_input(INKEY_LEFT, 0);
								 break;
					case SDLK_D: player_input(INKEY_DOWN, 0);
								 break;
					case SDLK_F: player_input(INKEY_RIGHT, 0);
								 break;
				}
			}
		}

		/* Game update */
		update_player();

		glNamedBufferData(gl.uniform_buffer[PLAYER_UBUF_IDX],
				sizeof(player), &player, GL_STATIC_DRAW);
		glNamedBufferData(gl.uniform_buffer[VIEW_UBUF_IDX],
				sizeof(view), &view, GL_STATIC_DRAW);

		/* Render */
		int w, h;
		SDL_GetWindowSize(gl.window, &w, &h);
		glViewport(0, 0, w, h);
		glScissor(0, 0, w, h);
		view.width = w;
		view.height = h;

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glUseProgram(gl.sprite_program);
		glBindVertexArray(gl.v_array);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glUseProgram(gl.tile_program);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 4);

		SDL_GL_SwapWindow(gl.window);

		/* Frame advance */
		monotime.tv_nsec += (1000000000 / 60);
		if (monotime.tv_nsec >= 1000000000) {
			monotime.tv_nsec -= 1000000000;
			monotime.tv_sec++;
		}
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &monotime, NULL);
	}

	return 0;
}
