
main: src/main.c src/simple_image.c src/string_art.c
	gcc -Wall -Wextra $^ -o $@ -lm
