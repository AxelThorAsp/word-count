CC = gcc
CFLAGS = -g -Wall -Werror -std=c99 -m64
wc: main.c
	$(CC) $(CFLAGS) -o wclone main.c
