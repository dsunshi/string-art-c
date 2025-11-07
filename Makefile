
BUILD_TYPE ?= release

CFLAGS =-std=c99 -Wall -Wextra -pedantic-errors -Warith-conversion

ifeq ($(BUILD_TYPE), debug)
	CFLAGS += -g -Og -Wconversion
else
	CFLAGS += -O3 -Wfloat-conversion -DNDEBUG
endif

main: src/main.c src/simple_image.c src/string_art.c
	$(CC) $(CFLAGS) $^ -o $@ -lm

.PHONY:clean
clean:
	rm -vf main 
