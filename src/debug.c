#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glut.h>

void debug_msg() {
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
