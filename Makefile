PKGCONF = `pkg-config --libs --cflags gl glut sdl3`

make:
	gcc -o bin *.c -lm $(PKGCONF)
