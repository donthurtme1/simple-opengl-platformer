#include "global.h"

void move_player(int x, int y) {
	player.vel_x = x;
	player.vel_y = y;
}

/* Called every frame, update player position, state, etc. */
void update_player() {
	player.pos_x += player.vel_x;
	player.pos_y += player.vel_y;
}
