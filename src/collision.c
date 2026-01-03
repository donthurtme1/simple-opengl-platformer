#include "types.h"

#define SIGN_BIT_32 (1 << 31)

/* Returns 1 if counterclockwise, -1 if clockwise and 0 if collinear */
static inline int orientation(struct Vec2 v, struct Vec2 w) {
	int weird_dot_product = (v.y * w.x) - (v.x * w.y);
	if (weird_dot_product == 0)
		return 0;
	else if (weird_dot_product & SIGN_BIT_32)
		return -1;
	else
		return 1;
}

/* Returns 1 if intersect, 0 if no intersect and -1 on failure */
int line_line_intersect
(struct Vec2 p, struct Vec2 q, /* Line segment 1 */
 struct Vec2 r, struct Vec2 s, /* Line segment 2 */
 struct Vec2 *intersect /* Return */
 ) {
	struct Vec2 pq = { q.x - p.x, q.y - p.y }; /* line segment 1 */
	struct Vec2 qr = { r.x - q.x, r.y - q.y };
	struct Vec2 qs = { s.x - q.x, s.y - q.y };

	struct Vec2 rs = { s.x - r.x, s.y - r.y }; /* line segment 2 */
	struct Vec2 sp = { p.x - s.x, p.y - s.y };
	struct Vec2 sq = { q.x - s.x, q.y - s.y };

	int ori1 = orientation(pq, qr);
	int ori2 = orientation(pq, qs);
	int ori3 = orientation(rs, sp);
	int ori4 = orientation(rs, sq);

	if (((ori1 == ori2) && ori1) || ((ori3 == ori4) && ori3))
		return 0; /* Same orientation of points => no intersection */

	/* Calculate scalar value */
	int top = ((p.x - r.x)*(r.y - s.y)) - ((p.y - r.y)*(r.x - s.x));
	int bottom = ((p.x - q.x)*(r.y - s.y)) - ((p.y - q.y)*(r.x - s.x));
	if (bottom == 0)
		return -1;

	float scalar = (float)top / bottom;
	intersect->x = p.x + (int)(scalar * (q.x - p.x));
	intersect->y = p.y + (int)(scalar * (q.y - p.y));
	return 1;
}

/* Returns -1 on failure.
 * Find the intersection between the line defined by `p`
 * and `q` and `rect`.
 * Return coordinates in `intersect` and intersecting side ID
 * in `side` */
int line_rect_intersect
(struct Vec2 p, struct Vec2 q, /* `p` and `q` define the line segment */
 struct Rect rect,
 struct Vec2 *intersect, RectFace *side /* Return args */
 ) {
	int ret;

	/* Check vertical intersection */
	if (p.y <= rect.y) { /* Line starts from below rect */
		struct Vec2 rect_p = { rect.x         , rect.y };
		struct Vec2 rect_q = { rect.x + rect.w, rect.y };
		ret = line_line_intersect(p, q, rect_p, rect_q, intersect);
		if (ret == 1) {
			*side = FACE_BOTTOM;
			return 1;
		}
	} else if (p.y >= rect.y + rect.h) { /* Starts above */
		struct Vec2 rect_p = { rect.x         , rect.y + rect.h };
		struct Vec2 rect_q = { rect.x + rect.w, rect.y + rect.h };
		ret = line_line_intersect(p, q, rect_p, rect_q, intersect);
		if (ret == 1) {
			*side = FACE_TOP;
			return 1;
		}
	}

	/* Check horizontal intersection */
	if (p.x <= rect.x) { /* Line starts from left of rect */
		struct Vec2 rect_p = { rect.x, rect.y          };
		struct Vec2 rect_q = { rect.x, rect.y + rect.h };
		ret = line_line_intersect(p, q, rect_p, rect_q, intersect);
		if (ret == 1) {
			*side = FACE_LEFT;
			return 1;
		}
	} else if (p.x >= rect.x + rect.w) { /* Starts right */
		struct Vec2 rect_p = { rect.x + rect.w, rect.y          };
		struct Vec2 rect_q = { rect.x + rect.w, rect.y + rect.h };
		ret = line_line_intersect(p, q, rect_p, rect_q, intersect);
		if (ret == 1) {
			*side = FACE_RIGHT;
			return 1;
		}
	}

	return 0;
}
