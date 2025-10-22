#include "global.h"

void player_input(enum PlayerInput key, bool key_down) {
	/* Check movement */
	if (key & (INKEY_UP|INKEY_LEFT|INKEY_DOWN|INKEY_RIGHT)) {
		if (key_down) {
			player.key_bitmask |= key;
			if (key & (INKEY_UP|INKEY_DOWN)) {
				if (key == INKEY_UP)
					player.y_input = 1;
				else 
					player.y_input = -1;
			} else {
				if (key == INKEY_LEFT)
					player.x_input = -1;
				else
					player.x_input = 1;
			}
		} else {
			player.key_bitmask &= ~key;
			if (key == INKEY_UP) {
				if (player.key_bitmask & INKEY_DOWN)
					player.y_input = -1;
				else
					player.y_input = 0;
			} else if (key == INKEY_LEFT) {
				if (player.key_bitmask & INKEY_RIGHT)
					player.x_input = 1;
				else
					player.x_input = 0;
			} else if (key == INKEY_DOWN) {
				if (player.key_bitmask & INKEY_UP)
					player.y_input = 1;
				else
					player.y_input = 0;
			} else if (key == INKEY_RIGHT) {
				if (player.key_bitmask & INKEY_LEFT)
					player.x_input = -1;
				else
					player.x_input = 0;
			}
		}
	}
}

void move_player(int x, int y) {
	player.vel_x = x * 2;
	player.vel_y = y * 2;
}

/* Called every frame, update player position, state, etc. */
void update_player() {
	player.vel_x = player.x_input * 20;
	player.vel_y = player.y_input * 20;
	player.pos_x += player.vel_x;
	player.pos_y += player.vel_y;
}
