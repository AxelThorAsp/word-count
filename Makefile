CC = gcc
CFLAGS = -g -O2 -Wall -Wextra -pedantic -m64
wc: main.c
	$(CC) $(CFLAGS) -o wclone main.c
