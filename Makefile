
main: main.c string_art.c
	gcc -Wall -Wextra $^ -o $@ -lm
