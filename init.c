#define GL_GLEXT_PROTOTYPES
#include <fcntl.h>
#include <GL/glut.h>
#include <SDL3/SDL.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "global.h"

/* Helper function to convert shader source file to a glsl shader,
 * then compile and check for errors.
 * Returns 0 on success and -1 otherwise */
static int loadshader(GLuint shader, const char *f_path) {
	/* Open and stat source file */
	int fd = open(f_path, O_RDONLY);
	struct stat info;
	fstat(fd, &info);

	/* Memory map the source file */
	char *src = mmap(0, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (src == MAP_FAILED) {
		perror("mmap");
		close(fd);
		return -1;
	}

	/* Add source to the shader, then close mmap and file */
	glShaderSource(shader, 1, (const char **)&src, (int *)&info.st_size);
	munmap(src, info.st_size);
	close(fd);

	/* Compile shader */
	int compilation_status = 0;
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compilation_status);
	if (compilation_status == GL_FALSE) {
		int len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		char log[len];
		glGetShaderInfoLog(shader, len, &len, log);
		write(2, log, len);
	}

	return 0;
}

/* Load, compile and link shaders into a shader program,
 * returns 0 on success and -1 on failure */
int createprogram
(GLuint *program,			/* Pointer to the shader program to link to */
 const char *vert_name,		/* Names of the shaders to link */
 const char *frag_name) {
	int ret = 0;
	GLuint vert_shader, frag_shader;
	vert_shader = glCreateShader(GL_VERTEX_SHADER);
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

	/* TODO: determine shader dir at runtime */
	const char shader_dir[] = "/home/basil/c/games/platformer/shaders/";
	char vert_pathname[sizeof(shader_dir) + strlen(vert_name)];
	char frag_pathname[sizeof(shader_dir) + strlen(frag_name)];
	strcpy(vert_pathname, shader_dir);
	strcat(vert_pathname, vert_name);
	strcpy(frag_pathname, shader_dir);
	strcat(frag_pathname, frag_name);
	loadshader(vert_shader, vert_pathname);
	loadshader(frag_shader, frag_pathname);

	int link_res;
	*program = glCreateProgram();
	glAttachShader(*program, vert_shader);
	glAttachShader(*program, frag_shader);
	glLinkProgram(*program);
	glGetProgramiv(*program, GL_LINK_STATUS, &link_res);
	if (link_res == GL_FALSE) {
		int len = 0;
		glGetProgramiv(*program, GL_INFO_LOG_LENGTH, &len);

		char log[len];
		glGetProgramInfoLog(*program, len, &len, log);
		write(2, log, len);
		ret = -1;
	}

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	return ret;
}

/* Initialise renderer.
 * Returns 0 on success and -1 otherwise */
int init_all() {
	/* Set SDL3 OpenGL attributes */
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	/* Create main SDL3 window and context */
	gl.window = SDL_CreateWindow("Ink", 1920, 1080,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	gl.context = SDL_GL_CreateContext(gl.window);
	SDL_GL_MakeCurrent(gl.window, gl.context);

	/* Initialise glut library */
	int argc = 0;
	char *argv[2] = {0, 0};
	glutInit(&argc, argv);
	glClearColor(0.0f, 0.0f, 0.12f, 1.0f);
	glLineWidth(2.0f);
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glDisable(GL_STENCIL_TEST);

	/* Window size */
	int w, h;
	SDL_GetWindowSize(gl.window, &w, &h);
	glViewport(0, 0, w, h);
	glScissor(0, 0, w, h);
	view.width = w;
	view.height = h;

	/* Create shader programs */
	int res;
	res = createprogram(&gl.sprite_program,
			"sprite_vert.glsl", "sprite_frag.glsl");
	if (res == -1)
		return -1;


	/* Create and initialise uniform buffers */
	glGenBuffers(sizeof(gl.uniform_buffer), gl.uniform_buffer);
	glBindBufferBase(GL_UNIFORM_BUFFER, PLAYER_UBUF_IDX,
			gl.uniform_buffer[PLAYER_UBUF_IDX]);
	glBindBufferBase(GL_UNIFORM_BUFFER, VIEW_UBUF_IDX,
			gl.uniform_buffer[VIEW_UBUF_IDX]);

	glNamedBufferData(gl.uniform_buffer[PLAYER_UBUF_IDX],
			sizeof(player), &player, GL_STATIC_DRAW);
	glNamedBufferData(gl.uniform_buffer[VIEW_UBUF_IDX],
			sizeof(view), &view, GL_STATIC_DRAW);


	float data[6] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f,
	};
	//unsigned int vbuf;
	//glGenBuffers(1, &vbuf);

	glGenVertexArrays(1, &gl.array);
	glBindVertexArray(gl.array);

	//glBindBuffer(GL_ARRAY_BUFFER, vbuf);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float[2]), 0);
	//glEnableVertexAttribArray(0);

	return 0;
}
