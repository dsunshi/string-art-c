
main: src/main.c src/simple_image.c
	gcc -Wall -Wextra $^ -o $@ -lm
