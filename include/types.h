#ifndef _TYPES_H
#define _TYPES_H

#define RETURN 

typedef enum {
	FACE_TOP,
	FACE_BOTTOM,
	FACE_LEFT,
	FACE_RIGHT,
} RectFace;

typedef union {
	struct {
		unsigned int x_fract : 8;
		int x_whole : 24;

		unsigned int y_fract : 8;
		int y_whole : 24;
	};
	struct {
		int x_raw;
		int y_raw;
	};
} Coords;

struct Vec2 {
	int x, y;
};

struct Rect {
	int x, y;
	int w, h;
};

#endif /* _TYPES_H */
