#include "global.h"
#include "types.h"

/* `p` and `q` define the line segment */
extern int line_rect_intersect(
		struct Vec2 p, struct Vec2 q, struct Rect rect,
		RETURN struct Vec2 *intersect, RETURN RectFace *side);


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
				if (key == INKEY_LEFT) {
					player.x_input = -1;
					player.face_left = true;
				} else {
					player.x_input = 1;
					player.face_left = false;
				}
			}
		} else {
			player.key_bitmask &= ~key;
			if (key == INKEY_UP) {
				if (player.key_bitmask & INKEY_DOWN)
					player.y_input = -1;
				else
					player.y_input = 0;
			} else if (key == INKEY_LEFT) {
				if (player.key_bitmask & INKEY_RIGHT) {
					player.x_input = 1;
					player.face_left = false;
				} else {
					player.x_input = 0;
				}
			} else if (key == INKEY_DOWN) {
				if (player.key_bitmask & INKEY_UP)
					player.y_input = 1;
				else
					player.y_input = 0;
			} else if (key == INKEY_RIGHT) {
				if (player.key_bitmask & INKEY_LEFT) {
					player.x_input = -1;
					player.face_left = true;
				} else {
					player.x_input = 0;
				}
			}
		}
	} else if ((key & INKEY_JUMP) && key_down) {
		player.pos.y += 1; /* TODO: this is kind of a hack */
		player.vel.y = 70;
	}
}

/* Called every frame, update player position, state, etc. */
void update_player(unsigned int frame_count) {
	player.vel.x = player.x_input * 20;
	player.vel.y -= 3;

	struct Vec2 old = { player.pos.x, player.pos.y };

	player.pos.x += player.vel.x;
	player.pos.y += player.vel.y;
	/* Vertical collision */
	//if (player.pos.y + player.vel.y < -1536) {
	//	player.pos.y = -1536;
	//	player.vel.y = 0;
	//} else {
	//	player.pos.y += player.vel.y;
	//}

	/* TODO: order of blocks in level_data could effect
	 * how collision is handled */
	for (int i = 0; i < LEN(level_data) && level_data[i].tileid != TILE_NONE; i++) {
		struct Vec2 intersect;
		RectFace side;
		struct Rect scaled_terrain = {
			.x = level_data[i].area.x * (16 * 16),
			.y = level_data[i].area.y * (16 * 16),
			.w = level_data[i].area.w * (16 * 16),
			.h = level_data[i].area.h * (16 * 16),
		};
		int ret = line_rect_intersect(
				old, player.pos, scaled_terrain,
				&intersect, &side);
		if (ret != 1)
			continue;

		/* Don't collide if moving out of collision.
		 * Avoids trapping player in collision and also makes jumping
		 * work (touching the floor would otherwise count as colliding) */
		if (side == FACE_TOP && player.vel.y < 0) {
			player.pos.y = intersect.y;
			player.vel.y = 0;
		}
	}

	if (player.x_input != 0) {
		player.anim_id = 1;
	} else {
		player.anim_id = 0;
	}

	if (frame_count % 10 == 0) {
		player.anim_frame += 1;
		player.anim_frame %= 4;
	}
}
