PKGCONF = `pkg-config --libs --cflags gl glut sdl3`

make:
	gcc -o bin -g src/*.c -Iinclude -lm $(PKGCONF)
