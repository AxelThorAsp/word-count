CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -m64
wc: main.c
	$(CC) $(CFLAGS) -o wclone main.c
