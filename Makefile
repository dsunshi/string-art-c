
main: src/main.c src/simple_image.c src/string_art.c
	gcc -std=c99 -Wall -Wextra -pedantic-errors -Wconversion -Warith-conversion $^ -o $@ -lm
