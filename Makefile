
main: main.c
	gcc -Wall -Wextra $< -o %@ -lm

.PHONY clean
clean:
	rm main
