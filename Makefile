all:
	gcc -std=c99 -pedantic -Wall -Wextra -Wno-restrict -Wno-format-security -Iinclude -o solution main.c functions.c morse_lib.c -lm

